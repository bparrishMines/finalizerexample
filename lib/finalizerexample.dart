import 'dart:ffi'; // For FFI
import 'dart:io'; // For Platform.isX

final DynamicLibrary exampleLib = Platform.isAndroid
    ? DynamicLibrary.open("libexample_lib.so")
    : DynamicLibrary.process();

final void Function(Pointer<Void>) initializeDL = exampleLib.lookupFunction<
    Void Function(Pointer<Void>),
    void Function(Pointer<Void>)>('initialize_dl');

final void Function() createJObject = exampleLib
    .lookupFunction<Void Function(), void Function()>('create_jobject');

final void Function(Object) attachFinalizer =
    exampleLib.lookupFunction<Void Function(Handle), void Function(Object)>(
        'attach_finalizer');

class MyClass {
  MyClass() {
    print('create');
    createJObject();
    print('attach');
    attachFinalizer(this);
  }
}
