; XFAIL: *

; RUN: opt -S -dse < %s | FileCheck %s

; We DSE stack alloc'ed and byval locations, in the presence of fences.
; Fence does not make an otherwise thread local store visible.
; Right now the DSE in presence of fence is only done in end blocks (with no successors),
; but the same logic applies to other basic blocks as well.
; The store to %addr.i can be removed since it is a byval attribute
define void @test3(ptr byval(i32) %addr.i) {
; CHECK-LABEL: @test3
; CHECK-NOT: store
; CHECK: fence
; CHECK: ret
  store i32 5, ptr %addr.i, align 4
  fence release
  ret void
}

declare void @foo(ptr nocapture %p)

declare noalias ptr @malloc(i32)

; DSE of stores in locations allocated through library calls.
define void @test_nocapture() {
; CHECK-LABEL: @test_nocapture
; CHECK: malloc
; CHECK: foo
; CHECK-NOT: store
; CHECK: fence
  %m  =  call ptr @malloc(i32 24)
  call void @foo(ptr %m)
  store i8 4, ptr %m
  fence release
  ret void
}


; This is a full fence, but it does not make a thread local store visible.
; We can DSE the store in presence of the fence.
define void @fence_seq_cst() {
; CHECK-LABEL: @fence_seq_cst
; CHECK-NEXT: fence seq_cst
; CHECK-NEXT: ret void
  %P1 = alloca i32
  store i32 0, ptr %P1, align 4
  fence seq_cst
  store i32 4, ptr %P1, align 4
  ret void
}
