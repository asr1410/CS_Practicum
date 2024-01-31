import matplotlib.pyplot as plt
import math

values = []
times_3 = []
times_5 = []
times_7 = []

count = 0
with open("/content/output.txt", "r") as file:
    for line in file:
        columns = line.strip().split()

        if count > 15:
            if len(columns) >= 7:
                values.append(float(columns[0]))
                times_3.append(math.log(float(columns[2])))
                times_5.append(math.log(float(columns[4])))
                times_7.append(math.log(float(columns[6])))
        count += 1
plt.figure(figsize=(10, 6))
plt.plot(values, times_3, label="recursion", marker="o")
plt.plot(values, times_5, label="dp cache", marker="s")
plt.plot(values, times_7, label="dp non cache", marker="^")

plt.xlabel("Time")
plt.ylabel("Value")
plt.title("Value vs. Time")
plt.legend()

plt.grid(True)
plt.show()
