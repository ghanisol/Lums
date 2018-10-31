; ModuleID = 'hadamard.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@.str = private unnamed_addr constant [8 x i8] c"out.dat\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.3 = private unnamed_addr constant [29 x i8] c"diff -w out.dat out.gold.dat\00", align 1
@stdout = external global %struct._IO_FILE*, align 8
@.str.4 = private unnamed_addr constant [47 x i8] c"*********************************************\0A\00", align 1
@.str.5 = private unnamed_addr constant [47 x i8] c"FAIL: Output DOES NOT match the golden output\0A\00", align 1
@.str.6 = private unnamed_addr constant [45 x i8] c"*******************************************\0A\00", align 1
@.str.7 = private unnamed_addr constant [45 x i8] c"PASS: The output matches the golden output!\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct._IO_FILE*, align 8
  %3 = alloca [128 x i16], align 16
  %4 = alloca i32, align 4
  %5 = alloca [128 x i16], align 16
  %6 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %7 = call %struct._IO_FILE* @fopen(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0))
  store %struct._IO_FILE* %7, %struct._IO_FILE** %2, align 8
  store i32 0, i32* %4, align 4
  br label %8

; <label>:8:                                      ; preds = %17, %0
  %9 = load i32, i32* %4, align 4
  %10 = icmp slt i32 %9, 128
  br i1 %10, label %11, label %20

; <label>:11:                                     ; preds = %8
  %12 = load i32, i32* %4, align 4
  %13 = trunc i32 %12 to i16
  %14 = load i32, i32* %4, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [128 x i16], [128 x i16]* %3, i64 0, i64 %15
  store i16 %13, i16* %16, align 2
  br label %17

; <label>:17:                                     ; preds = %11
  %18 = load i32, i32* %4, align 4
  %19 = add nsw i32 %18, 1
  store i32 %19, i32* %4, align 4
  br label %8

; <label>:20:                                     ; preds = %8
  %21 = getelementptr inbounds [128 x i16], [128 x i16]* %5, i32 0, i32 0
  %22 = getelementptr inbounds [128 x i16], [128 x i16]* %3, i32 0, i32 0
  %23 = call i32 @fastWalshTransform(i16* %21, i16* %22, i16 zeroext 7)
  store i32 0, i32* %6, align 4
  br label %24

; <label>:24:                                     ; preds = %35, %20
  %25 = load i32, i32* %6, align 4
  %26 = icmp slt i32 %25, 128
  br i1 %26, label %27, label %38

; <label>:27:                                     ; preds = %24
  %28 = load %struct._IO_FILE*, %struct._IO_FILE** %2, align 8
  %29 = load i32, i32* %6, align 4
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds [128 x i16], [128 x i16]* %5, i64 0, i64 %30
  %32 = load i16, i16* %31, align 2
  %33 = zext i16 %32 to i32
  %34 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %28, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i32 %33)
  br label %35

; <label>:35:                                     ; preds = %27
  %36 = load i32, i32* %6, align 4
  %37 = add nsw i32 %36, 1
  store i32 %37, i32* %6, align 4
  br label %24

; <label>:38:                                     ; preds = %24
  %39 = load %struct._IO_FILE*, %struct._IO_FILE** %2, align 8
  %40 = call i32 @fclose(%struct._IO_FILE* %39)
  %41 = call i32 @system(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.3, i32 0, i32 0))
  %42 = icmp ne i32 %41, 0
  br i1 %42, label %43, label %50

; <label>:43:                                     ; preds = %38
  %44 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8
  %45 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %44, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.4, i32 0, i32 0))
  %46 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8
  %47 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %46, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.5, i32 0, i32 0))
  %48 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8
  %49 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %48, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.4, i32 0, i32 0))
  store i32 1, i32* %1, align 4
  br label %57

; <label>:50:                                     ; preds = %38
  %51 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8
  %52 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %51, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.6, i32 0, i32 0))
  %53 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8
  %54 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %53, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.7, i32 0, i32 0))
  %55 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8
  %56 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %55, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.6, i32 0, i32 0))
  store i32 0, i32* %1, align 4
  br label %57

; <label>:57:                                     ; preds = %50, %43
  %58 = load i32, i32* %1, align 4
  ret i32 %58
}

declare %struct._IO_FILE* @fopen(i8*, i8*) #1

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #1

declare i32 @fclose(%struct._IO_FILE*) #1

declare i32 @system(i8*) #1

; Function Attrs: nounwind uwtable
define i32 @fastWalshTransform(i16*, i16*, i16 zeroext) #0 {
  %4 = alloca i16*, align 8
  %5 = alloca i16*, align 8
  %6 = alloca i16, align 2
  %7 = alloca i16, align 2
  %8 = alloca i16, align 2
  %9 = alloca i16, align 2
  %10 = alloca i16, align 2
  %11 = alloca i16, align 2
  %12 = alloca i16, align 2
  %13 = alloca i16, align 2
  %14 = alloca i16, align 2
  %15 = alloca i16, align 2
  store i16* %0, i16** %4, align 8
  store i16* %1, i16** %5, align 8
  store i16 %2, i16* %6, align 2
  %16 = load i16, i16* %6, align 2
  %17 = zext i16 %16 to i32
  %18 = shl i32 1, %17
  %19 = trunc i32 %18 to i16
  store i16 %19, i16* %7, align 2
  store i16 0, i16* %8, align 2
  br label %20

; <label>:20:                                     ; preds = %36, %3
  %21 = load i16, i16* %8, align 2
  %22 = zext i16 %21 to i32
  %23 = load i16, i16* %7, align 2
  %24 = zext i16 %23 to i32
  %25 = icmp slt i32 %22, %24
  br i1 %25, label %26, label %39

; <label>:26:                                     ; preds = %20
  %27 = load i16, i16* %8, align 2
  %28 = zext i16 %27 to i64
  %29 = load i16*, i16** %5, align 8
  %30 = getelementptr inbounds i16, i16* %29, i64 %28
  %31 = load i16, i16* %30, align 2
  %32 = load i16, i16* %8, align 2
  %33 = zext i16 %32 to i64
  %34 = load i16*, i16** %4, align 8
  %35 = getelementptr inbounds i16, i16* %34, i64 %33
  store i16 %31, i16* %35, align 2
  br label %36

; <label>:36:                                     ; preds = %26
  %37 = load i16, i16* %8, align 2
  %38 = add i16 %37, 1
  store i16 %38, i16* %8, align 2
  br label %20

; <label>:39:                                     ; preds = %20
  %40 = load i16, i16* %7, align 2
  %41 = zext i16 %40 to i32
  %42 = ashr i32 %41, 1
  %43 = trunc i32 %42 to i16
  store i16 %43, i16* %9, align 2
  br label %44

; <label>:44:                                     ; preds = %122, %39
  %45 = load i16, i16* %9, align 2
  %46 = zext i16 %45 to i32
  %47 = icmp sge i32 %46, 1
  br i1 %47, label %48, label %127

; <label>:48:                                     ; preds = %44
  store i16 0, i16* %10, align 2
  br label %49

; <label>:49:                                     ; preds = %113, %48
  %50 = load i16, i16* %10, align 2
  %51 = zext i16 %50 to i32
  %52 = load i16, i16* %7, align 2
  %53 = zext i16 %52 to i32
  %54 = icmp slt i32 %51, %53
  br i1 %54, label %55, label %121

; <label>:55:                                     ; preds = %49
  store i16 0, i16* %11, align 2
  br label %56

; <label>:56:                                     ; preds = %109, %55
  %57 = load i16, i16* %11, align 2
  %58 = zext i16 %57 to i32
  %59 = load i16, i16* %9, align 2
  %60 = zext i16 %59 to i32
  %61 = icmp slt i32 %58, %60
  br i1 %61, label %62, label %112

; <label>:62:                                     ; preds = %56
  %63 = load i16, i16* %10, align 2
  %64 = zext i16 %63 to i32
  %65 = load i16, i16* %11, align 2
  %66 = zext i16 %65 to i32
  %67 = add nsw i32 %64, %66
  %68 = add nsw i32 %67, 0
  %69 = trunc i32 %68 to i16
  store i16 %69, i16* %12, align 2
  %70 = load i16, i16* %10, align 2
  %71 = zext i16 %70 to i32
  %72 = load i16, i16* %11, align 2
  %73 = zext i16 %72 to i32
  %74 = add nsw i32 %71, %73
  %75 = load i16, i16* %9, align 2
  %76 = zext i16 %75 to i32
  %77 = add nsw i32 %74, %76
  %78 = trunc i32 %77 to i16
  store i16 %78, i16* %13, align 2
  %79 = load i16, i16* %12, align 2
  %80 = zext i16 %79 to i64
  %81 = load i16*, i16** %4, align 8
  %82 = getelementptr inbounds i16, i16* %81, i64 %80
  %83 = load i16, i16* %82, align 2
  store i16 %83, i16* %14, align 2
  %84 = load i16, i16* %13, align 2
  %85 = zext i16 %84 to i64
  %86 = load i16*, i16** %4, align 8
  %87 = getelementptr inbounds i16, i16* %86, i64 %85
  %88 = load i16, i16* %87, align 2
  store i16 %88, i16* %15, align 2
  %89 = load i16, i16* %14, align 2
  %90 = zext i16 %89 to i32
  %91 = load i16, i16* %15, align 2
  %92 = zext i16 %91 to i32
  %93 = sub nsw i32 %90, %92
  %94 = trunc i32 %93 to i16
  %95 = load i16, i16* %13, align 2
  %96 = zext i16 %95 to i64
  %97 = load i16*, i16** %4, align 8
  %98 = getelementptr inbounds i16, i16* %97, i64 %96
  store i16 %94, i16* %98, align 2
  %99 = load i16, i16* %14, align 2
  %100 = zext i16 %99 to i32
  %101 = load i16, i16* %15, align 2
  %102 = zext i16 %101 to i32
  %103 = add nsw i32 %100, %102
  %104 = trunc i32 %103 to i16
  %105 = load i16, i16* %12, align 2
  %106 = zext i16 %105 to i64
  %107 = load i16*, i16** %4, align 8
  %108 = getelementptr inbounds i16, i16* %107, i64 %106
  store i16 %104, i16* %108, align 2
  br label %109

; <label>:109:                                    ; preds = %62
  %110 = load i16, i16* %11, align 2
  %111 = add i16 %110, 1
  store i16 %111, i16* %11, align 2
  br label %56

; <label>:112:                                    ; preds = %56
  br label %113

; <label>:113:                                    ; preds = %112
  %114 = load i16, i16* %9, align 2
  %115 = zext i16 %114 to i32
  %116 = shl i32 %115, 1
  %117 = load i16, i16* %10, align 2
  %118 = zext i16 %117 to i32
  %119 = add nsw i32 %118, %116
  %120 = trunc i32 %119 to i16
  store i16 %120, i16* %10, align 2
  br label %49

; <label>:121:                                    ; preds = %49
  br label %122

; <label>:122:                                    ; preds = %121
  %123 = load i16, i16* %9, align 2
  %124 = zext i16 %123 to i32
  %125 = ashr i32 %124, 1
  %126 = trunc i32 %125 to i16
  store i16 %126, i16* %9, align 2
  br label %44

; <label>:127:                                    ; preds = %44
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0, !0}

!0 = !{!"clang version 3.9.1-4ubuntu3~16.04.2 (tags/RELEASE_391/rc2)"}
