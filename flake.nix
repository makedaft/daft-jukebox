{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";

    gfx-font-converter-source = {
      url = "github:adafruit/Adafruit-GFX-Library";
      flake = false;
    };
  };

  outputs = { self, nixpkgs, flake-utils, gfx-font-converter-source, ... }:
    let
      shell = { pkgs }:
        let
          gfx-fontconvert = pkgs.stdenv.mkDerivation {
            name = "adafruit-gfx-fontconvert";
            src = gfx-font-converter-source;
            # buildInputs = with pkgs; [ python3 ];
            nativeBuildInputs = with pkgs; [ makeWrapper gcc freetype ];
            buildPhase = ''
              ls -la;
              cd fontconvert;
              gcc -I"${pkgs.freetype.dev}/include/freetype2" fontconvert.c -o fontconvert -lfreetype -lm;
            '';
            installPhase = ''
              mkdir -p $out/bin;
              cp ./fontconvert $out/bin/fontconvert;
            '';
          };
        in pkgs.buildFHSUserEnv {
          name = "owyn-jukebox-env";
          targetPkgs = pkgs: with pkgs; [
            (hiPrio gcc)
            platformio-core
            avrdude
            openocd
            clang-tools
            just
            glibc
            unixtools.xxd

            gfx-fontconvert
          ];
          multiPkgs = pkgs: (with pkgs; [ udev ]);

          runScript = "zsh";
          profile = ''
            export DIRENV_DISABLE_HOOK=1;
            export WITH_NIX_PREFIX="fhs";
          '';
        };
    in flake-utils.lib.eachDefaultSystem
    (system:
      let pkgs = import nixpkgs { inherit system; };
      in { devShells.default = (shell { inherit pkgs; }).env; });
}
