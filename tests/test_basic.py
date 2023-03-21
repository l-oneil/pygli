import pygli
import shutil
import numpy as np
from pathlib import Path


def test_version():
    assert pygli.__version__ == "0.0.1"


def test_load():
    # Test for shape / dtype correctness
    img = pygli.load("data/kueken7_rgba16_sfloat.dds")
    expected_shape = [256, 256, 4]
    assert list(img.shape) == expected_shape
    assert img.dtype == np.float32

    img = pygli.load("data/kueken7_rgba8_unorm.dds")
    expected_shape = [256, 256, 4]
    assert list(img.shape) == expected_shape
    assert img.dtype == np.uint8

    img = pygli.load("data/array_r8_uint.dds")
    expected_shape = [256, 256, 1]
    assert list(img.shape) == expected_shape
    assert img.dtype == np.uint8

    # Test for assert condition on missing file
    failed = False
    try: 
        img = pygli.load("not_a_file.dds")
    except:
        failed = True
    assert(failed)


def test_save():
    formats = {
        pygli.Format.R8_UNORM_PACK8 : {"ch" : 1, "dtype" : np.uint8},
        pygli.Format.RG8_UNORM_PACK8 : {"ch" : 2, "dtype" : np.uint8},
        pygli.Format.RGB8_UNORM_PACK8 : {"ch" : 3, "dtype" : np.uint8},
        pygli.Format.RGBA8_UNORM_PACK8 : {"ch" : 4, "dtype" : np.uint8},
        
        pygli.Format.R16_UNORM_PACK16 : {"ch" : 1, "dtype" : np.uint16},
        pygli.Format.RG16_UNORM_PACK16 : {"ch" : 2, "dtype" : np.uint16},
        pygli.Format.RGB16_UNORM_PACK16 : {"ch" : 3, "dtype" : np.uint16},
        pygli.Format.RGBA16_UNORM_PACK16 : {"ch" : 4, "dtype" : np.uint16},

        pygli.Format.R32_SFLOAT_PACK32 : {"ch" : 1, "dtype" : np.float32},
        pygli.Format.RG32_SFLOAT_PACK32 : {"ch" : 2, "dtype" : np.float32},
        pygli.Format.RGB32_SFLOAT_PACK32 : {"ch" : 3, "dtype" : np.float32},
        pygli.Format.RGBA32_SFLOAT_PACK32 : {"ch" : 4, "dtype" : np.float32},
    }

    out_dir = Path("test_output")
    out_dir.mkdir(parents=True, exist_ok=True)
    failed = False
    for idx, (k, v) in enumerate(formats.items()):
        try:
            ones = np.ones(shape=[128, 256, v["ch"]], dtype=v["dtype"])
            failed |=  pygli.save(f"{str(out_dir)}/{idx:04d}.dds", ones, k), f"Failed on: {k}"
        except Exception as e:
            print(f"Exception Hit: {e}")
            print(f"Format Failed: {k}, {v['ch'], v['dtype']}")
    assert not failed
    
    # Tidy Up
    shutil.rmtree(out_dir)
