// Import the functions you need from the SDKs you need
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.13.0/firebase-app.js";
import {
  getDatabase,
  ref,
  onValue,
  set,
} from "https://www.gstatic.com/firebasejs/9.13.0/firebase-database.js";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
const firebaseConfig = {
  apiKey: "AIzaSyAooiV-1_tM_iv11utRPmLIVGjHKk17ypw",
  authDomain: "iot-project-fcc11.firebaseapp.com",
  databaseURL: "https://iot-project-fcc11-default-rtdb.firebaseio.com",
  projectId: "iot-project-fcc11",
  storageBucket: "iot-project-fcc11.appspot.com",
  messagingSenderId: "19278660475",
  appId: "1:19278660475:web:b474ed77ac81fbd6bff3de",
  measurementId: "G-E4BG7Z8G69",
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getDatabase(app);

const body = document.querySelector("body");
const checkBox = document.getElementById("toggleB");
const arus = document.getElementById("arus");
const daya = document.getElementById("daya");

const dbRef = ref(db);

checkBox.addEventListener("change", function () {
  if (checkBox.checked) {
    console.log(true);
    set(dbRef, {
      LED_STATUS: 1,
      sensor: {
        arus: 0,
        daya: 0,
      },
    });
    body.classList.add("active");
  } else {
    console.log(false);
    set(dbRef, {
      LED_STATUS: 0,
      sensor: {
        arus: 0,
        daya: 0,
      },
    });
    body.classList.remove("active");
  }
});

onValue(dbRef, (snapshot) => {
  const data = snapshot.val();
  console.log(data.LED_STATUS);
  console.log(data.sensor);
  arus.innerHTML = data.sensor.arus + " A";
  daya.innerHTML = data.sensor.daya + " Watt";
  if (data.LED_STATUS) {
    checkBox.checked = true;
    body.classList.add("active");
  } else {
    checkBox.checked = false;
    body.classList.remove("active");
  }
});
