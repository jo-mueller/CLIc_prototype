

#include "cleMinimumOfAllPixelsKernel.hpp"
#include "cleMemory.hpp"
#include "cleMinimumXProjectionKernel.hpp"
#include "cleMinimumYProjectionKernel.hpp"
#include "cleMinimumZProjectionKernel.hpp"

namespace cle
{

MinimumOfAllPixelsKernel::MinimumOfAllPixelsKernel (const ProcessorPointer &device) : Operation (device, 2)
{
}

auto
MinimumOfAllPixelsKernel::SetInput (const Image &object) -> void
{
    this->AddParameter ("src", object);
}

auto
MinimumOfAllPixelsKernel::SetOutput (const Image &object) -> void
{
    this->AddParameter ("dst", object);
}

auto
MinimumOfAllPixelsKernel::Execute () -> void
{
    auto src = this->GetImage ("src");
    auto dst = this->GetImage ("dst");
    std::array<size_t, 3> dim = src->Shape ();

    if (dim[2] > 1)
        {
            dim[2] = 1;
            auto temp = Memory::AllocateObject (this->Device (), dim, dst->BitType ().Get (), dst->MemType ().Get ());

            MinimumZProjectionKernel kernel (this->Device ());
            kernel.SetInput (*src);
            kernel.SetOutput (temp);
            kernel.Execute ();
            src = std::make_shared<Image> (temp);
        }

    if (dim[1] > 1)
        {
            dim[1] = 1;
            auto temp = Memory::AllocateObject (this->Device (), dim, dst->BitType ().Get (), dst->MemType ().Get ());

            MinimumYProjectionKernel kernel (this->Device ());
            kernel.SetInput (*src);
            kernel.SetOutput (temp);
            kernel.Execute ();
            src = std::make_shared<Image> (temp);
        }

    MinimumXProjectionKernel kernel (this->Device ());
    kernel.SetInput (*src);
    kernel.SetOutput (*dst);
    kernel.Execute ();
}

} // namespace cle
