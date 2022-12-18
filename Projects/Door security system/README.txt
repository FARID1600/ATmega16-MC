Developing a door locker security system that asks at the initial state
to give a password to store it in its EEPROM. The next times it asks for
this password. If the password is correct, then rotate the motor CW for
15 seconds then ACW for another 15 (to open and close the electric door).
If the password is incorrect for 3 consecutive times, start the buzzer.
Notice that the password is changeable and the 3 consecutive times are
whether from entering the password to login or to change it.

Some notes to start:
Password should be integers only, the keypad doesn't accept characters.
Enter is '=' button.
If you pressed a wrong button, you can clear the password by pressing ON/C button.
NB: You can't use it after writing all the 5-digits.
The buzzer is activated when 3 wrong passwords are entered. The 3 times could be from choice '+' or '-' accumulated.
If the buzzer stopped, then the user entered a wrong password. The buzzer is activated from the first time.
If a correct password is entered, the 3-times wrong passwords to activate the buzzer are reset (Buzzer needs 3 incorrect passwords).