// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'typeset' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef LIBTYPESET_MATH_ATOM_H
#define LIBTYPESET_MATH_ATOM_H

#include "tex/symbol.h"
#include "tex/math/mathonoff.h"

#include <memory>

namespace tex
{

namespace math
{

class LIBTYPESET_API Atom : public Node
{
public:
  enum Type
  {
    Ord = 0,
    Op = 1,
    Bin = 2,
    Rel = 3,
    Open = 4,
    Close = 5,
    Punct = 6,
    Inner = 7,
    Over,
    Under,
    Acc,
    Rad,
    Vcent
  };

  enum LimitsFlag
  {
    NoLimits,
    Limits,
    DisplayLimits,
  };

  bool isAtom() const override;

  inline Type type() const { return mType; }
  void changeType(Type newtype);

  inline const std::shared_ptr<Node> & nucleus() const { return mNucleus; }
  inline const std::shared_ptr<Node> & subscript() const { return mSubscript; }
  inline const std::shared_ptr<Node> & superscript() const { return mSuperscript; }
  inline const std::shared_ptr<Symbol> & accent() const { return mAccent; }
  inline LimitsFlag limits() const { return mLimits; }

  void changeNucleus(const std::shared_ptr<Node> & nuc);
  void clearSubSupscripts();

  template<Atom::Type T, typename = std::enable_if_t<T == Atom::Op>>
  static std::shared_ptr<Atom> create(std::shared_ptr<Node> nucleus, std::shared_ptr<Node> subscript = nullptr, std::shared_ptr<Node> superscript = nullptr, LimitsFlag limits = NoLimits)
  {
    return std::make_shared<Atom>(T, nucleus, subscript, superscript, nullptr, limits);
  }

  template<Atom::Type T, typename = std::enable_if_t<T == Atom::Acc>>
  static std::shared_ptr<Atom> create(std::shared_ptr<Node> nucleus, std::shared_ptr<Symbol> accent, std::shared_ptr<Node> subscript = nullptr, std::shared_ptr<Node> superscript = nullptr)
  {
    return std::make_shared<Atom>(T, nucleus, subscript, superscript, accent, NoLimits);
  }

  template<Atom::Type T, typename = std::enable_if_t<T != Atom::Acc && T != Atom::Op>>
  static std::shared_ptr<Atom> create(std::shared_ptr<Node> nucleus, std::shared_ptr<Node> subscript = nullptr, std::shared_ptr<Node> superscript = nullptr)
  {
    return std::make_shared<Atom>(T, nucleus, subscript, superscript, nullptr, NoLimits);
  }

public:
  Atom(Type t, std::shared_ptr<Node> nucleus, std::shared_ptr<Node> subscript, std::shared_ptr<Node> superscript, std::shared_ptr<Symbol> accent, LimitsFlag limits);

private:
  Type mType;
  std::shared_ptr<Node> mNucleus;
  std::shared_ptr<Node> mSubscript;
  std::shared_ptr<Node> mSuperscript;
  std::shared_ptr<Symbol> mAccent; // accent of a Acc atom
  LimitsFlag mLimits;
};

} // namespace math

} // namespace tex

#endif // LIBTYPESET_MATH_ATOM_H
