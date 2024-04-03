
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  nfc.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Scan an ID:");
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    if(tag.hasNdefMessage()){
      NdefMessage message = tag.getNdefMessage();
      int recordCount = message.getRecordCount();
      for (int i = 0; i < recordCount; i++){
        NdefRecord record = message.getRecord(i);
        int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
        record.getPayload(payload);
        String payloadAsString = "";
        for (int c = 0; c < payloadLength; c++) {
          payloadAsString += (char)payload[c];
        }
        Serial.println("IDMessage:" + payloadAsString);
        //Serial.write(payload, payloadLength);
        //PrintHexChar(payload, payloadLength);
      }
    }
  }
  
  delay(3000);

}
