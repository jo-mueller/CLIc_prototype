

#include "cleBlockEnumerateKernel.hpp"

namespace cle
{

BlockEnumerateKernel::BlockEnumerateKernel(std::shared_ptr<GPU> t_gpu) : 
    Kernel( t_gpu,
            "block_enumerate",
            {"src0", "src1", "dst", "scalar"}
    )
{
    this->m_Sources.insert({this->m_KernelName, this->m_OclHeader});
}

void BlockEnumerateKernel::SetInput(Object& t_x)
{
    this->AddObject(t_x, "src0");
}

void BlockEnumerateKernel::SetInputSums(Object& t_x)
{
    this->AddObject(t_x, "src1");
}

void BlockEnumerateKernel::SetOutput(Object& t_x)
{
    this->AddObject(t_x, "dst");
}

void BlockEnumerateKernel::SetBlocksize(int t_x)
{
    this->AddObject(t_x, "scalar");
}

void BlockEnumerateKernel::Execute()
{
    this->ManageDimensions();
    this->BuildProgramKernel();
    this->SetArguments();
    this->EnqueueKernel();
}

} // namespace cle
