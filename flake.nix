{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    let
      shell = { pkgs }: pkgs.buildFHSUserEnv {
        name = "owyn-jukebox-env";
        targetPkgs = pkgs: with pkgs; [
          (hiPrio gcc)
          platformio-core
          avrdude
          openocd
          clang-tools
          just
          glibc
          # clang
        ];
        multiPkgs = pkgs: (with pkgs; [ udev ]);

        runScript = "zsh";
        profile = "export DIRENV_DISABLE_HOOK=1;";
      };
    in flake-utils.lib.eachDefaultSystem
    (system:
      let pkgs = import nixpkgs { inherit system; };
      in { devShells.default = (shell { inherit pkgs; }).env; });
}
