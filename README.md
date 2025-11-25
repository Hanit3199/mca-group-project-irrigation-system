# Design a System to Optimize Irrigation Scheduling Based on Crop Type, Soil Moisture, and Weather Conditions

## 📌 Overview
This project is a **group-based MCA Semester-1 system design** focused on optimizing irrigation scheduling.  
The system uses **crop type**, **soil moisture level**, and **weather forecast data** to determine whether irrigation is needed and to automate irrigation timing.

The goal is to **reduce water wastage** and **increase crop efficiency** using a rule-based decision system.

---

## 🧠 Problem Statement
Traditional irrigation systems often rely on guesswork or fixed schedules, leading to:

- Over-irrigation or water wastage  
- Under-irrigation causing crop stress  
- No consideration of weather changes (rainfall)  
- No adaptation to different crop needs  

**We aim to design a smart decision-based irrigation scheduler** that decides:
- When to irrigate  
- How much irrigation is needed  
- Which crop needs priority  

---

## 🎯 Project Objectives
- Analyze crop-wise water requirements  
- Monitor soil moisture levels  
- Use weather conditions (e.g., rainfall prediction)  
- Apply an algorithm to decide irrigation need  
- Reduce manual effort and water usage  
- Improve irrigation efficiency

---

## 🚀 Features
- 📌 Crop-wise irrigation thresholds  
- 📌 Soil moisture sensor input  
- 📌 Weather forecast integration  
- 📌 Automated irrigation decision  
- 📌 Real-time evaluation  
- 📌 User-friendly result output  
- 📌 Modular code structure  

---

## 🛠️ System Workflow
1. **Input crop type**  
2. **Input soil moisture percentage**  
3. **Input weather forecast**  
4. System checks:
   - Crop moisture requirement  
   - Threshold comparison  
   - Weather impact  
5. **Outputs whether irrigation is needed or not**

---

## 📂 Folder / Code Structure (Suggested)
```
/mca-group-project-irrigation-system
│
├── main.c / main.java / main.py     # Main logic file
├── crop_data.txt                    # Crop-wise moisture thresholds
├── README.md                        # Documentation
├── images/                          # Screenshots
└── ... (other source files)
```

---

## 💻 How to Run (Generic)
### **For C**
```
gcc main.c -o irrigation
./irrigation
```

### **For Java**
```
javac Main.java
java Main
```

### **For Python**
```
python main.py
```

---

## 👥 Group Members
| Name          | Roll No |
|---------------|---------|
| Dhannu Kumar  | 10      |
| Hanit Kumar   | 11      |
| Basiru Mbye   | 08      |
| Isha Dua      | 12      |

---

## 🧾 Technologies Used
- C / Java / Python (as per implementation)
- File handling (optional)
- Conditional logic & DSA concepts
- Weather forecast logic (rule-based)

---

## 📸 Output Screenshots
*(Add your program screenshots in an `/images` folder and showcase them here)*

---

## ✅ Conclusion
This system provides a **smart, efficient, and optimized irrigation scheduler** capable of handling real-time environmental factors such as soil moisture and weather predictions.  
It helps conserve water and supports better agriculture planning.

