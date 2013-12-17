#include "specwriterimpl.h"
#include "../../apngasm.h"
#include <sstream>
#include <boost/property_tree/json_parser.hpp>

namespace apngasm {
  namespace spec {
    namespace priv {

        // Initialize AbstractSpecWriterImpl object.
        AbstractSpecWriterImpl::AbstractSpecWriterImpl(const APNGAsm* pApngasm)
          : _pApngasm(pApngasm)
        {
          // nop
        }

        // Initialize JsonSpecWriterImpl object.
        JsonSpecWriterImpl::JsonSpecWriterImpl(const APNGAsm* pApngasm)
          : AbstractSpecWriterImpl(pApngasm)
        {
          // nop
        }

        // Write APNGAsm object to spec file.
        // Return true if write succeeded.
        bool JsonSpecWriterImpl::write(const std::string& filePath, const std::string& currentDir) const
        {
          boost::property_tree::ptree root;

          // Write apngasm fields.
          // root.put("name", _pApngasm->name());
          // root.put("loops", _pApngasm->loops());
          // root.put("skip_first", _pApngasm->skipFirst());

          {
            boost::property_tree::ptree child;
            std::vector<APNGFrame>& frames = const_cast<std::vector<APNGFrame>&>(_pApngasm->getFrames());
            const int count = frames.size();
            for(int i = 0;  i < count;  ++i)
            {
              std::ostringstream file;
              std::ostringstream delay;
              file << i << ".png";
              delay << frames[i].delayNum() << "/" << frames[i].delayDen();
              child.push_back(std::make_pair(file.str(), delay.str()));
            }
            root.add_child("frames", child);
          }

          write_json(filePath, root);
          return true;
        }

        // Initialize XmlSpecWriterImpl object.
        XmlSpecWriterImpl::XmlSpecWriterImpl(const APNGAsm* pApngasm)
          : AbstractSpecWriterImpl(pApngasm)
        {
          // nop
        }

        // Write APNGAsm object to spec file.
        // Return true if write succeeded.
        bool XmlSpecWriterImpl::write(const std::string& filePath, const std::string& currentDir) const
        {
          return false;
        }


    } // namespace priv
  } // namespace spec
} // namespace apngasm
