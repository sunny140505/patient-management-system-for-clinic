# patient-management-system-for-clinic
Patient management system for clinics . Our code allows to add patient , add emergency patient , allows to search and display patient using mobile number. Each patient is represented patient class which contains information like first name, last name , blood group, problem, mobile number , age , gender , emergency condition. Our code has two queues  one for emergency patients and other for regular patients. We have added CSV file that allows us to save patient data even if code is restart or closed. Code loads existing patient data from CSV file. we have created a hash map for quick access to patient data using mobile number. Our code has functions  "takepatienttodoctor" that removes patient from the queue and displays the information of removed patient. "searchmobile" shows patient data using mobile number. "displaypatient" shows all the patient information.
