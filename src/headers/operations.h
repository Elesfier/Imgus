
#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "operation.h"

#include "src/operations/cut.cpp"
#include "src/operations/move.cpp"
#include "src/operations/blending.cpp"
#include "src/operations/copy.cpp"
#include "src/operations/close.cpp"
#include "src/operations/open.cpp"
#include "src/operations/dilatation.cpp"
#include "src/operations/division.cpp"
#include "src/operations/lowpass.cpp"
#include "src/operations/erosion.cpp"
#include "src/operations/exponentiation.cpp"
#include "src/operations/gradient.cpp"
#include "src/operations/histogram.cpp"
#include "src/operations/stretching.cpp"
#include "src/operations/global-thresholding.cpp"
#include "src/operations/local-thresholding.cpp"
#include "src/operations/multi-thresholding.cpp"
#include "src/operations/log.cpp"
#include "src/operations/mediana.cpp"
#include "src/operations/multiplication.cpp"
#include "src/operations/nthRoot.cpp"
#include "src/operations/sum.cpp"
#include "src/operations/highpass.cpp"

namespace Operations
{
  template<typename null_t = nullptr_t>
  void SETUP_OPERATION(Operations::Operation* op)
  {
    //FIXME for what reason, I made this??
    OperationsDefinition::get().ops.push_back({
           op,
           op->englishName,
           op->polishName,
           op->fileExt,
           op->hasParams,
           op->params,
           op->isMulti
    });
  }

  template<typename null_t = nullptr_t>
  void SETUP_OPERATIONS()
  {
    SETUP_OPERATION(new Sum());
    SETUP_OPERATION(new Blending());
    SETUP_OPERATION(new Exponentiation());
    SETUP_OPERATION(new NthRoot());
    SETUP_OPERATION(new Log());
    SETUP_OPERATION(new Move());
    SETUP_OPERATION(new Cut());
    SETUP_OPERATION(new Copy());
    SETUP_OPERATION(new Histogram());
    SETUP_OPERATION(new Stretching());
    SETUP_OPERATION(new GlobalThresholding());
    SETUP_OPERATION(new LocalThresholding());
    SETUP_OPERATION(new MultiThresholding());
    SETUP_OPERATION(new Dilatation());
    SETUP_OPERATION(new Erosion());
    SETUP_OPERATION(new Open());
    SETUP_OPERATION(new Close());
    SETUP_OPERATION(new Lowpass());
    SETUP_OPERATION(new Highpass());
    SETUP_OPERATION(new Mediana());
    SETUP_OPERATION(new Gradient());
    SETUP_OPERATION(new Multiplication());
    SETUP_OPERATION(new Division());
  }
}

#endif //OPERATIONS_H
