import 'dart:ffi';

import 'package:finalizerexample/finalizerexample.dart';
import 'package:flutter/material.dart';

void main() {
  initializeDL(NativeApi.initializeApiDLData);
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  MyClass? instance;

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Center(
            child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            ElevatedButton(
              child: Text('Toggle Instance'),
              onPressed: () {
                if (instance == null) {
                  print('Instantiating a new MyClass object.');
                  instance = MyClass();
                } else {
                  print('Removing reference to MyClass object.');
                  instance = null;
                }
              },
            ),
            ElevatedButton(
              onPressed: () {
                List<int>.generate(100, (index) => 100);
              },
              child: Text('Encourage GC'),
            )
          ],
        )),
      ),
    );
  }
}
