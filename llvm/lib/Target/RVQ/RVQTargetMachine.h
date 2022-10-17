#ifndef LLVM_LIB_TARGET_RISCVQR_RISCVQRTARGETMACHINE_H
#define LLVM_LIB_TARGET_RISCVQR_RISCVQRTARGETMACHINE_H

#include "RISCVQRSubtarget.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Target/TargetMachine.h"
#include <memory>

namespace llvm {

class Module;

class RVQTargetMachine : public LLVMTargetMachine {
    const DataLayout DataLayout;       // Calculates type size & alignment
    SparcSubtarget Subtarget;
    SparcInstrInfo InstrInfo;
    RVQFrameInfo FrameInfo;

protected:
    virtual const TargetAsmInfo *createTargetAsmInfo() const;

public:
    RVQTargetMachine(const Module &M, const std::string &FS);

    virtual const RVQInstrInfo *getInstrInfo() const {return &InstrInfo; }
    virtual const RVQFrameInfo *getFrameInfo() const {return &FrameInfo; }
    virtual const RVQSubtarget *getSubtargetImpl() const{return &Subtarget; }
    virtual const RVQRegisterInfo *getRegisterInfo() const {
    return &InstrInfo.getRegisterInfo();
  }
    virtual const DataLayout *getDataLayout() const { return &DataLayout; }
    static unsigned getModuleMatchQuality(const Module &M);

  // Pass Pipeline Configuration
    virtual bool addInstSelector(PassManagerBase &PM, bool Fast);
    virtual bool addPreEmitPass(PassManagerBase &PM, bool Fast);
};

} // end namespace llvm

/*
class RVQTargetMachine : public LLVMTargetMachine {
    std::unique_ptr<TargetLoweringObjectFIle> TLOF;
    mutable StringMap<std::unique_ptr<RISCVSubtarget>> SubtargetMap;

public:
    RVQTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options,
                   Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                   CodeGenOpt::Level OL, bool JIT);

    const X86Subtarget *getSubtargetImpl(const Function &F) const override;
    // DO NOT IMPLEMENT: There is no such thing as a valid default subtarget,
    // subtargets are per-function entities based on the target-specific
    // attributes of each function.
    const X86Subtarget *getSubtargetImpl() const = delete;

    TargetTransformInfo getTargetTransformInfo(const Function &F) const override;

    // Set up the pass pipeline.
    TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

    TargetLoweringObjectFile *getObjFileLowering() const override {
        return TLOF.get();
    }

};
} // end namespace llvm

#endif
*/
