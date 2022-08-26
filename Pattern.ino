//------------------ โปรแกรมในการวิ่งอัตโนมัติ -----------------------//

void Brown() {
  oled(0, 0, "DEC= %d Brown", x);

  // -- เริ่ม Method ในการวิ่งจากจุด Start -- //
  // -- ไปวางที่จุดสีน้ำตาล และกลับจุด Start-- //

  Start();

  RRR();

  FFF();

  FFF_Can();
  PlaceCan();

  FFF();

  LLL();

  Finish();

  // -- สิ้นสุดโปรแกรม -- //
}
void Pink() {
  oled(0, 0, "DEC= %d Pink", x);

  // -- เริ่ม Method ในการวิ่งจากจุด Start -- //
  // -- ไปวางที่จุดสีชมพู และกลับจุด Start-- //

  Start();
  FFF();
  FFF();
  RRR();
  FFF();
  FFF();
  FFF();
  FFF_Can();
  PlaceCan();
  FFF();
  FFF();
  FFF();
  LLL();
  FFF();
  FFF();
  Finish();

  // -- สิ้นสุดโปรแกรม -- //
}
void Orange() {
  oled(0, 0, "DEC= %d Orange", x);

  // -- เริ่ม Method ในการวิ่งจากจุด Start -- //
  // -- ไปวางที่จุดสีส้ม และกลับจุด Start-- //

  Start();
  FFF();
  FFF();
  FFF();
  FFF();
  RRR();
  FFF();
  FFF();
  FFF();
  FFF_Can();
  PlaceCan();
  FFF();
  FFF();
  FFF();
  LLL();
  FFF();
  FFF();
  FFF();
  FFF();
  Finish();
  // -- สิ้นสุดโปรแกรม -- //
}
void Yellow() {
  oled(0, 0, "DEC= %d yellow", x);

  // -- เริ่ม Method ในการวิ่งจากจุด Start -- //
  // -- ไปวางที่จุดสีเหลือง และกลับจุด Start-- //

  Start();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  RRR();
  FFF();
  FFF_Can();
  PlaceCan();
  FFF();
  LLL();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  Finish();
  // -- สิ้นสุดโปรแกรม -- //
}
void Green() {
  oled(0, 0, "DEC= %d Green", x);

  // -- เริ่ม Method ในการวิ่งจากจุด Start -- //
  // -- ไปวางที่จุดสีเขียว และกลับจุด Start-- //

  Start();
  RRR();
  LLL();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF_Can();
  PlaceCan();
  RRR();
  LLL();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  Finish();
  // -- สิ้นสุดโปรแกรม -- //
}
void Blue() {
  oled(0, 0, "DEC= %d Blue", x);

  // -- เริ่ม Method ในการวิ่งจากจุด Start -- //
  // -- ไปวางที่จุดสีน้ำเงิน และกลับจุด Start-- //

  Start();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  LLL();
  RRR();
  FFF();
  FFF_Can();
  PlaceCan();
  FFF();
  LLL();
  RRR();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  Finish();
  // -- สิ้นสุดโปรแกรม -- //
}
void Purple() {
  oled(0, 0, "DEC= %d Purple", x);

  // -- เริ่ม Method ในการวิ่งจากจุด Start -- //
  // -- ไปวางที่จุดสีม่วง และกลับจุด Start-- //

  Start();

  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();

  LLL();

  FFF();
  FFF();

  RRR();

  FFF();
  FFF();
  FFF();

  FFF_Can();
  PlaceCan();

  FFF();
  FFF();

  LLL();

  FFF();
  FFF();

  RRR();

  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();
  FFF();

  Finish();
  // -- สิ้นสุดโปรแกรม -- //
}

//-------------------- สิ้นสุดโค้ดวิ่งอัตโนมัติ ----------------//
