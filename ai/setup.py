##
## EPITECH PROJECT, 2021
## zappy_ai
## File description:
## setup
##

from distutils.core import setup, Extension

if __name__ == "__main__":
    setup(name="zappy_networking",
          version="1.0.0",
          description="Python interface for socket networking",
          author="huntears",
          author_email="dev@huntears.com",
          license="GNU General Public License v3.0",
          platforms="GNU/Linux",
          ext_modules=[Extension(
              "zappy_networking",
              sources = [
                  "src/module.c",
                  "src/connect.c",
                  "src/disconnect.c",
                  "src/receive.c",
                  "src/send.c"
              ],
              include_dirs=[
                  "."
              ],
              language= "en"
          )])
else:
    print("Can you not ?")
