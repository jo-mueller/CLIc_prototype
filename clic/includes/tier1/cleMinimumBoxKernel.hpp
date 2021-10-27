
#ifndef __cleMinimumBoxKernel_hpp
#define __cleMinimumBoxKernel_hpp

#include "cleKernel.hpp"

namespace cle
{
    
class MinimumBoxKernel : public Kernel
{
private:
    std::string m_OclHeader2d = 
        #include "cle_minimum_separable_2d.h" 
        ;
    std::string m_OclHeader3d = 
        #include "cle_minimum_separable_3d.h" 
        ;

public:
    MinimumBoxKernel(std::shared_ptr<GPU>);
    void SetInput(Buffer&);
    void SetOutput(Buffer&);
    void SetRadius(float=0, float=0, float=0);
    void Execute();

private:
    float m_x;
    float m_y;
    float m_z;
    int Radius2KernelSize(float) const;
};

} // namespace cle

#endif // __cleMinimumBoxKernel_hpp
