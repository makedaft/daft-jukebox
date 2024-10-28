build:
  pio run -e esp32;

check:
  pio check --skip-packages

upload:
  pio run -e esp32 -t upload

clean:
  pio run -t clean

update:
  pio pkg update

monitor:
  pio device monitor

test:
  pio test -e test

format:
  find include/ src/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i

devsetup:
  # COMPILATIONDB_INCLUDE_TOOLCHAIN=true pio run -t compiledb
  ./setup_compiledb.sh

circuit:
  cd wiring && latexmk -f -auxdir=.cache/tex -outdir=../media -interaction=nonstopmode -lualatex ./wiring.tex
  magick -density 200x200 ./media/wiring.pdf -background white -alpha remove -alpha off ./media/wiring.png

circuit-dev:
  npx nodemon --exec 'clear && just circuit' -e .tex
