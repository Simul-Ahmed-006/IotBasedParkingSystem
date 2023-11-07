// //https://script.google.com/macros/s/AKfycby5aw-q4J27XMba20n6rkB4HkkBKVsOawTf1qQGr5j41mlc4uzd678cH1p51_2SGfyM7w/exec?sts=write&slot0=Off&slot1=Success&slot2=32.5&slot3=95&slot4=Off&slot5=Off

//https://script.google.com/macros/s/AKfycbxfpTnnOKiEMfuQl27zGJYC5FlZGwsYChWg2SADcFa3irRiqW7KANLUVstId7dQTkLC/exec?sts=write&slot0=Off&slot1=Success&slot2=32.5&slot3=95&slot4=Off&slot5=Off


//https://script.google.com/macros/s/AKfycbxH2YFUoJlK5gbdAPRbTenfnH1EOCIYJcpihqYTNwW39po1JwOg07n4iBhm27LZCHYO/exec?sts=write&slot0=Off&slot1=Success&slot2=32.5&slot3=95&slot4=Off&slot5=Off
  function doGet(e) { 
  var result = 'Ok';
  
  if (e.parameter === undefined) {
    result = 'No Parameters';
  } else {
    var sheet_id = '1pMUYZ12TcrwTuVA16vAakEirb1efe5Wezj_xp_a-33M'; 	// Spreadsheet ID.
    var sheet_name = "ParkingSystem1";  // Sheet Name in Google Sheets.

    var sheet_open = SpreadsheetApp.openById(sheet_id);
    var sheet_target = sheet_open.getSheetByName(sheet_name);

    var newRow = 3;  // Always write to row 3

    // Data variables
    var dataLog = [];
    var latestData = [];

    // Use 'Asia/Dhaka' timezone for the date and time
    var Curr_Date = Utilities.formatDate(new Date(), "Asia/Dhaka", 'dd/MM/yyyy');
    dataLog.push(Curr_Date);
    latestData.push(Curr_Date);

    var Curr_Time = Utilities.formatDate(new Date(), "Asia/Dhaka", 'HH:mm:ss');
    dataLog.push(Curr_Time);
    latestData.push(Curr_Time);

    for (var param in e.parameter) {
      if (param === 'sts') {
        var sts_val = stripQuotes(e.parameter[param]);

        if (sts_val === 'write') {
          // Process data parameters
          for (var i = 0; i < 6; i++) {
            var paramName = 'slot' + i;
            var value = stripQuotes(e.parameter[paramName]);
            dataLog.push(value);
            latestData.push(value);
          }

          // Get the range for the "Latest DHT11 Sensor Data" section (row 3)
          var RangeDataLatest = sheet_target.getRange('A3:H3');
          // Update the values for row 3
          RangeDataLatest.setValues([latestData]);
        } else {
          result = 'Invalid sts parameter value';
        }
      }
    }
  }

  return ContentService.createTextOutput(result);
}

function stripQuotes(value) {
  return value.replace(/^["']|['"]$/g, "");
}
