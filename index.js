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
  apiKey: "AIzaSyBQ48wb9YO1Zik_LaOgKvClB62THOIucvs",
  authDomain: "iot-tes-cb168.firebaseapp.com",
  databaseURL: "https://iot-tes-cb168.firebaseio.com",
  projectId: "iot-tes-cb168",
  storageBucket: "iot-tes-cb168.appspot.com",
  messagingSenderId: "740767901331",
  appId: "1:740767901331:web:aa31aecdbe82b0393c4f66",
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getDatabase(app);

const body = document.querySelector("body");
const checkBox = document.getElementById("toggleB");

const dbRef = ref(db);

checkBox.addEventListener("change", function () {
  if (checkBox.checked) {
    console.log(true);
    set(dbRef, {
      LED_STATUS: 1,
    });
    body.classList.add("active");
  } else {
    console.log(false);
    set(dbRef, {
      LED_STATUS: 0,
    });
    body.classList.remove("active");
  }
});

onValue(dbRef, (snapshot) => {
  const data = snapshot.val();
  console.log(data.LED_STATUS);
  if (data.LED_STATUS) {
    checkBox.checked = true;
    body.classList.add("active");
  } else {
    checkBox.checked = false;
    body.classList.remove("active");
  }
});
