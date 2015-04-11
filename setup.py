from distutils.core import setup, Extension

setup(
        name = 'python3-mmhash',
        version = '1.0',
        maintainer = 'Gilles Gagniard',
        maintainer_email = 'gilles@gagniard.org',
        url = 'https://github.com/gillesgagniard/python3-mmhash',
        ext_modules = [
            Extension('mmhash', ['mmhash.cpp'],),
            ],
        description="MurmurHash2 http://murmurhash.googlepages.com/",
        long_description="""
murmurhash is a fast hash function ::
    >>> import mmhash

    >>> print(mmhash.get_unsigned_hash("stdyun.com zsp007@gmail.com"))
    11740402118952761905
    
    >>> print(mmhash.get_hash("stdyun.com zsp007@gmail.com"))
    -6706341954756789711


MurmurHash2 http://murmurhash.googlepages.com/
MurmurHash2, 64-bit versions, by Austin Appleby

Modified by changsheng@douban.com

Ported to Python3 by gilles@gagniard.org

zsp windows,linux python lib
"""
)
