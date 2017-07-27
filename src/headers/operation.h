
#ifndef OPERATION_H
#define OPERATION_H

#include <map>
#include <vector>
#include "common.h"
#include "image.h"

namespace Operations
{
  typedef std::vector <Image::Image*> ImagePack;
  typedef std::map <Common::String, Common::String> ParamsPack;

  class Operation
  {
  public:

      Common::String name;
      Common::String englishName;
      Common::String polishName;
      Common::String fileExt;
      bool hasParams;
      ParamsPack params;
      bool isMulti;
      bool sameFormat;
      bool disableBinary;
      bool disableGrayScale;
      bool disableRGB;
      bool isOnlyMulti;

      Operation()
      {
        name = "";
        englishName = "";
        polishName = "";
        fileExt = "_";
        hasParams = false;
        params = {};
        isMulti = false;
        sameFormat = true;
        disableBinary = false;
        disableGrayScale = false;
        disableRGB = false;
        isOnlyMulti = false;
      }

      virtual ~Operation(){}
      virtual void operate(Image::Image *img, ParamsPack params){ };
      virtual void operate(ImagePack pack, ParamsPack params){ };
  };

  template <typename null_t = nullptr_t>
  void operate(Image::Image *img, Operation *op, ParamsPack params)
  {
      return op->operate(img, params);
  }

  template <typename null_t = nullptr_t>
  void operate(ImagePack pack, Operation *op, ParamsPack params)
  {
      return op->operate(pack, params);
  }

  struct OperationDefinition
  {
      Operation* op;
      Common::String className;
      Common::String polishName;
      Common::String fileNameAddon;
      bool hasParams;
      ParamsPack paramsPack;
      bool isMulti;
  };

  class OperationsDefinition
  {
  public:
      static OperationsDefinition& get()
      {
          static OperationsDefinition instance;
          return instance;
      }
      std::vector<OperationDefinition> ops;
      OperationsDefinition(OperationsDefinition const&) = delete;
      void operator=(OperationsDefinition const&) = delete;
  private:
      OperationsDefinition() {};
  };

}

#endif //OPERATION_H
