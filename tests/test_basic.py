import pygli
import shutil
import numpy as np
from pathlib import Path


def test_version():
    assert pygli.__version__ == "0.0.1"


def test_load():
    img = pygli.load("data/kueken7_rgba16_sfloat.dds")
    expected_shape = [256, 256, 4]
    assert list(img.shape) == expected_shape

    img = pygli.load("data/kueken7_rgba8_unorm.dds")
    expected_shape = [256, 256, 4]
    assert list(img.shape) == expected_shape

    img = pygli.load("data/array_r8_uint.dds")
    expected_shape = [256, 256, 1]
    assert list(img.shape) == expected_shape


def test_save():
    formats = {
        pygli.Format.FORMAT_R8_UNORM_PACK8 : {"ch" : 1, "dtype" : np.uint8},
        pygli.Format.FORMAT_RG8_UNORM_PACK8 : {"ch" : 2, "dtype" : np.uint8},
        pygli.Format.FORMAT_RGB8_UNORM_PACK8 : {"ch" : 3, "dtype" : np.uint8},
        pygli.Format.FORMAT_RGBA8_UNORM_PACK8 : {"ch" : 4, "dtype" : np.uint8},
        
        pygli.Format.FORMAT_R16_UNORM_PACK16 : {"ch" : 1, "dtype" : np.uint16},
        pygli.Format.FORMAT_RG16_UNORM_PACK16 : {"ch" : 2, "dtype" : np.uint16},
        pygli.Format.FORMAT_RGB16_UNORM_PACK16 : {"ch" : 3, "dtype" : np.uint16},
        pygli.Format.FORMAT_RGBA16_UNORM_PACK16 : {"ch" : 4, "dtype" : np.uint16},

        pygli.Format.FORMAT_R32_SFLOAT_PACK32 : {"ch" : 1, "dtype" : np.float32},
        pygli.Format.FORMAT_RG32_SFLOAT_PACK32 : {"ch" : 2, "dtype" : np.float32},
        pygli.Format.FORMAT_RGB32_SFLOAT_PACK32 : {"ch" : 3, "dtype" : np.float32},
        pygli.Format.FORMAT_RGBA32_SFLOAT_PACK32 : {"ch" : 4, "dtype" : np.float32},
    }

    out_dir = Path("test_output")
    out_dir.mkdir(parents=True, exist_ok=True)
    for idx, (k, v) in enumerate(formats.items()):
        ones = np.zeros(shape=[128, 128, v["ch"]], dtype=v["dtype"])
        assert pygli.save(f"{str(out_dir)}/{idx:04d}.dds", ones, k), f"Failed on: {k}"

    # Tidy Up
    shutil.rmtree(out_dir)
