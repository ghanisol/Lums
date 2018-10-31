#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/IR/IRBuilder.h"
#include <map>
#include <iterator>
#include <numeric>


using namespace llvm;

std::string fname_count = "_Z10count_instPci";
std::string fname_printInfo = "_Z10print_infov";

namespace 
{
    struct DynamicInstructionsCount : public ModulePass
    {
        static char ID;

        DynamicInstructionsCount() : ModulePass(ID) {}

        virtual bool runOnModule(Module &M)
        {
            // to remove printf calls
            //std::vector<Instruction*> to_remove;

            // Function inst_count
            // Function type
            std::vector<Type*> fargs_count;
            fargs_count.push_back(Type::getInt8PtrTy(M.getContext()));
            fargs_count.push_back(IntegerType::get(M.getContext(),32));

            FunctionType *ftype_count = FunctionType::get(Type::getVoidTy(M.getContext()),
                                                        fargs_count,
                                                        false);
            // Create function
            Function *func_count = (Function*)M.getOrInsertFunction(fname_count,
                                                    ftype_count);

            // Function printInfo
            // Function type
            FunctionType *ftype_printInfo = FunctionType::get(Type::getVoidTy(M.getContext()),
                                                        false);
            // Create function
            Function *func_printInfo = (Function*)M.getOrInsertFunction(fname_printInfo,
                                                    ftype_printInfo);

            for (auto& F : M)
            {
                for (auto& B : F)
                {
                    for (auto& I : B)
                    {    

                        // Get required info
                        std::string inst_name = I.getOpcodeName();
                        int inst_code = I.getOpcode();

                        if (inst_name == "phi") continue;


                        // Create builder
                        auto* inst = &I;
                        IRBuilder<> builder(inst);


                        // Arguments for the function
                        std::vector<Value*> fparams_count;
                        Value *inst_name_ptr = builder.CreateGlobalStringPtr(inst_name.c_str());
                        Value *inst_code_ptr = builder.getInt32(inst_code);
                        fparams_count.push_back(inst_name_ptr);
                        fparams_count.push_back(inst_code_ptr);

                        // Create func. call
                        builder.CreateCall(func_count, fparams_count);

                        if (I.getParent()->getParent()->getName() == "main" && inst_name == "ret")
                        {
                            IRBuilder<> builder(inst);
                            builder.CreateCall(func_printInfo);
                        }

                    }

                }
            }

            return true;
        }
    };
}

char DynamicInstructionsCount::ID = 0;
static RegisterPass<DynamicInstructionsCount> X("dcount", "Dynamic Instructions Count Pass", false, false);

static void registerDynamicInstructionsCount(const PassManagerBuilder &,
                           legacy::PassManagerBase &PM) {
    PM.add(new DynamicInstructionsCount());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerDynamicInstructionsCount);