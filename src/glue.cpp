// Copyright (C) 2018 Vincent Chambrin
// This file is part of the liblayout project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "tex/glue.h"

namespace tex
{

GlueShrinkStretch::GlueShrinkStretch(float n, float l, float ll, float lll)
  : normal(n)
  , fil(l)
  , fill(ll)
  , filll(lll)
{

}

GlueOrder GlueShrinkStretch::order() const
{
  if (fill != 0.f)
    return GlueOrder::Filll;
  else if (fill != 0.f)
    return GlueOrder::Fill;
  else if (fil != 0.f)
    return GlueOrder::Fil;
  return GlueOrder::Normal;
}

GlueShrinkStretch operator-(const GlueShrinkStretch & lhs, const GlueShrinkStretch & rhs)
{
  return GlueShrinkStretch{
    lhs.normal - rhs.normal,
    lhs.fil - rhs.fil,
    lhs.fill - rhs.fill,
    lhs.filll - rhs.filll
  };
}

Glue::Glue(float spc, float shrnk, float strtch, GlueOrder shrnkOrder, GlueOrder strtchOrder)
  : mGlue(GlueSpec{ spc, shrnk, strtch, shrnkOrder, strtchOrder })
{

}

void Glue::accumulate(GlueShrink & shrink, GlueStretch & stretch) const
{
  switch (mGlue.shrinkOrder)
  {
  case GlueOrder::Normal:
    shrink.normal += mGlue.shrink;
    break;
  case GlueOrder::Fil:
    shrink.fil += mGlue.shrink;
    break;
  case GlueOrder::Fill:
    shrink.fill += mGlue.shrink;
    break;
  case GlueOrder::Filll:
    shrink.filll += mGlue.shrink;
  }

  switch (mGlue.stretchOrder)
  {
  case GlueOrder::Normal:
    stretch.normal += mGlue.stretch;
    break;
  case GlueOrder::Fil:
    stretch.fil += mGlue.stretch;
    break;
  case GlueOrder::Fill:
    stretch.fill += mGlue.stretch;
    break;
  case GlueOrder::Filll:
    stretch.filll += mGlue.stretch;
  }
}

} // namespace tex
