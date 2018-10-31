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

std::string fname_count = "_Z12count_branchPci";
std::string fname_printInfo = "_Z10print_infov";

namespace 
{
    struct ProfileBranchBias : public ModulePass
    {
        static char ID;

        ProfileBranchBias() : ModulePass(ID) {}

        virtual bool runOnModule(Module &M)
        {
            // to remove printf calls
            // std::vector<Instruction*> to_remove;

            // Function branch_count
            // Function type
            std::vector<Type*> fargs_count;
            fargs_count.push_back(Type::getInt8PtrTy(M.getContext()));
            fargs_count.push_back(IntegerType::get(M.getContext(),1));

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
                        
                        // Create builder
                        auto* inst = &I;
                        IRBuilder<> builder(inst);


                        if (inst_name == "br")
                        {

                            bool isCon = cast<BranchInst>(inst)->isConditional();
                            if (isCon)
                            {
                                // Arguments for the function
                                std::vector<Value*> fparams_count;
                                Value *func_name_ptr = builder.CreateGlobalStringPtr(I.getParent()->getParent()->getName());
                                //Value *inst_code_ptr = builder.getInt1(inst->getOperand(0));
                                fparams_count.push_back(func_name_ptr);
                                fparams_count.push_back(inst->getOperand(0));

                                // Create func. call
                                builder.CreateCall(func_count, fparams_count);    
                            }
                            
                        }

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

char ProfileBranchBias::ID = 0;
static RegisterPass<ProfileBranchBias> X("profilebb", "Profile Branch Bias Pass", false, false);

static void registerProfileBranchBias(const PassManagerBuilder &,
                           legacy::PassManagerBase &PM) {
    PM.add(new ProfileBranchBias());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerProfileBranchBias);