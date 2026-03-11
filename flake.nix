{
  inputs = {
    nixpkgs.url = "github:Nixos/nixpkgs/nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
    in
    {
      packages.x86_64-linux.default = pkgs.stdenv.mkDerivation {
        name = "cm_tlprint";

        buildInputs = with pkgs; [
          gnumake
        ];

        src = ./.;

        outputs = [
          "out"
        ];

        configurePhase = "";

        buildPhase = ''
          make all
        '';

        installPhase = ''
          mkdir -p $out/lib
          mkdir -p $out/usr/include

          install -m 555 ./build/*.a ./build/*.so $out/lib/
          cp -r ./include $out/usr/include
        '';
      };
      packages.x86_64-linux.test = pkgs.stdenv.mkDerivation {
        name = "cm_tlprint";

        buildInputs = with pkgs; [
          gnumake
        ];

        src = ./.;

        outputs = [
          "out"
        ];

        installPhase = ''
          mkdir -p $out/bin

          make clear
          make test

          install -m 555 ./build/test $out/bin/
        '';
      };
    };
}
