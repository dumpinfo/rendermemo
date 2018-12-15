# setup.py
from distutils.core import setup, Extension

setup(name="sample1", 
      ext_modules=[
        Extension("sample1",
                  ["mujo_objdec.cpp"],
                  include_dirs = ['..'],
                  language="c++",
                  )
        ]
)
