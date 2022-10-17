#include "RISCVQRTargetMachine.h"
#include "MCTargetDesc/RISCVQRMCTargetDesc.h"
#include "TargetInfo/RISCVQRTargetInfo.h"
#include "RISCVQR.h"
#include "RISCVQRCallLowering.h"
#include "RISVQRLegalizerInfo.h"
#include "RISCVQRMacroFusion.h"
#include "RISCVQRSubtarget.h"
#include "RISCVQRTargetObjectFile.h"
#include "RISCVQRTargetTransformInfo.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/ExecutionDomainFix.h"
#include "llvm/CodeGen/GlobalISel/CSEInfo.h"
#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/CodeGen/GlobalISel/IRTranslator.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelect.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/CodeGen/GlobalISel/Legalizer.h"
#include "llvm/CodeGen/GlobalISel/RegBankSelect.h"
#include "llvm/CodeGen/MachineScheduler.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/RegAllocRegistry.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Function.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Pass.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Transforms/CFGuard.h"
#include <memory>
#include <string>

using namespace llvm;

/* static cl::opt<bool> ???("RVQ",
    cl::desc("Enable???"),
    cl::init(true), cl::Hidden);

static cl::opt<???>
    Enable???("RVQ",


extern "C" LLVM_EXTERNAL_VISIBILTY void LLVMInitializeRVQTarget(){
    // Resgister the target
    RegisterTargetMachine<RVQTargetMachine> X(getTheRVQ32Target());
    RegisterTargetMachine<RVQTargetMachine> Y(getTheRVQ64Target());

    // ???
}

RVQTargetMachine::RVQTargetMachine(const Target &T, const Triple &TT,
        StringRef CPU, StringRef FS, const TargetOptions &Options,
        Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
        CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FS, Options,
            getEffectiveRelocModel(TT,)) // ????

const RVQSubtarget *
RVQTargetMachine::getSubtargetImpl(const Function &FF) const{
    Attribute CPUAttr = F.getFnAttribute("target-cpu");
    Arrtibute TuneArrr = F.getFnAttribute("tune-cpu");
    Attribute FSAttr = F.getFnAttribute("target-features");

    std::string CPU = CPUAttr.isValid()? CPUAttr.getValueAsString().str() : TargetCPU;
    std::string TuneCPU = TuneAttr.isValid()? TuneAttr.getValueAsString().str() : CPU;
    std::string FS = FSAttr.getValueAsString().str() : TargetFS;

    auto &O = SubtargetMap[Key];
    if (!I){
        resetTargetOptions(F)
    }
}
*/

RVQTargetMachine::RVQTargetMachine(const Module &M, const std::string &FS)
    : DataLayout("e-p:32:32-f128:128:128"), Subtarget(M, FS), InstrInfo(Subtarget),
    FrameInfo(RVQFrameInfo::StackGrowsDown, 8, 0){

    }
// An upper-case “E” in the string indicates a big-endian target data model.
// A lower-case “e” indicates little-endian.

// “p:” is followed by pointer information: size, ABI alignment, and preferred alignment.
// If only two figures follow “p:”, first value is pointer size, second value is both ABI and preferred alignment.

// “i”, “f”, “v”, or “a” (corresponding to integer, floating point, vector, or aggregate).
// “i”, “v”, or “a” are followed by ABI alignment and preferred alignment.
// “f” is followed by three values: size of long double -> then ABI alignment -> ABI preferred alignment.
