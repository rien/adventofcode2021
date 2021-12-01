{
  description = "Advent of Code 2021";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils/master";
  };
  outputs = {self,  nixpkgs, flake-utils, ... }:
  flake-utils.lib.eachDefaultSystem (system: 
  let
    pkgs = import nixpkgs {
      inherit system;
    };
  in with pkgs; {
    devShell = mkShell {
      buildInputs = [
        gcc
        hyperfine
      ];
    };
  });
}
