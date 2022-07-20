#include <iostream>

#include "dna_strand.hpp"

int main() {
  DNAstrand dna;
  DNAstrand one;

  dna.PushBack('s');
  dna.PushBack('h');
  dna.PushBack('a');
  dna.PushBack('a');
  dna.PushBack('r');
  dna.PushBack('o');
  dna.PushBack('n');
  dna.PushBack('r');
  dna.PushBack('o');

  one.PushBack('x');
  one.PushBack('x');
  one.PushBack('x');
  one.PushBack('x');
  one.PushBack('x');

  dna.SpliceIn("ro", one);

  dna.Display();
}