/*
 * grandom.cc
 *
 * This file is licensed under the GPLv2 or later
 *
 * Pseudo-random number generation
 *
 * Copyright (C) 2012 Fabio D'Urso <fabiodurso@hotmail.it>
 */

#include "grandom.h"

#include <random>

namespace
{

auto& grandom_engine()
{
  static thread_local std::default_random_engine engine{std::random_device{}()};
  return engine;
}

}

void grandom_fill(Guchar *buff, int size)
{
  auto& engine = grandom_engine();
  std::uniform_int_distribution<unsigned short> distribution{std::numeric_limits<Guchar>::min(), std::numeric_limits<Guchar>::max()};
  for (int index = 0; index < size; ++index) {
    buff[index] = distribution(engine);
  }
}

double grandom_double()
{
  auto& engine = grandom_engine();
  return std::generate_canonical<double, std::numeric_limits<double>::digits>(engine);
}
