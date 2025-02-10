#Summary

<p>This project runs an exe file as a background service sending a string of pc stats to an arduino uno over serial.</p>
<p>The string is then displayed on the connected 16x2 i2c display.</p>

#Requirements

<ul>
<li>Arduino Uno</li>
<li>16x2 LCD Display with i2c Board</li>
<li>Python</li>
<li>VSCode with Platform IO Extension</li>
</ul>

#How to Build

1. Install python dependencies (pip install requirements.txt)
2. Change COMPORT global variable to your arduino's serial com port
3. Create an exe using pyinstaller (pyinstaller app.spec)
4. Create a windows server using included bat file in dist folder

#Dependencies

<ul>
<li>Pythonnet</li>
<li>Libre Hardware Monitor (DLL File in Repo)</li>
<li>Liquid Crystal Library (Included in Repo)</li>
</ul>
