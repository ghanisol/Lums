#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <map>
#include <iterator>
#include <numeric>


using namespace llvm;

namespace 
{
    struct StaticInstructionsCount : public ModulePass
    {
        static char ID;
        std::map <std::string, int> instructions;  // map to store instruction/counts

        StaticInstructionsCount() : ModulePass(ID) {}

        virtual bool runOnModule(Module &M)
        {
            for (auto& F : M)
            {
                for (auto& B : F)
                {
                    for (auto& I : B)
                    {
                        std::string inst_name = I.getOpcodeName();
                        instructions[inst_name]++;
                    }
                }
            }
            
        }

        virtual void print(raw_ostream &OS, const Module* = nullptr) const
        {
            int tot = std::accumulate(instructions.begin(), instructions.end(), 0,
                                        [](const size_t a, const std::pair<std::string, size_t>& b) {return a + b.second;});

            for (auto inst : instructions)
            {
                outs() << inst.first << "\t" << inst.second << "\n";
            }
            outs() << "TOTAL" << "\t" << tot << "\n";
        }
    };
}

char StaticInstructionsCount::ID = 0;
static RegisterPass<StaticInstructionsCount> X("icount", "Static Instructions Count Pass", false, false);

static void registerStaticInstructionsCount(const PassManagerBuilder &,
                           legacy::PassManagerBase &PM) {
    PM.add(new StaticInstructionsCount());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerStaticInstructionsCount);