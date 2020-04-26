import csv
from matplotlib import pyplot as plt


with open('basecase1simple.csv', 'r') as csv_file:
    csv_reader = csv.reader(csv_file)

    # next(csv_reader)

    Index = []
    Grade_School = []
    Div_n_Conq = []
    Karatsuba = []
    for line in csv_reader:
        Index.append(float(line[0]))
        Grade_School.append(float(line[2]))
        Div_n_Conq.append(float(line[1]))
        Karatsuba.append(float(line[3]))



x = Index
y = Grade_School
z = Karatsuba
d = Div_n_Conq

plt.title("Algorithms Assymptotics")
plt.xlabel("Number of Digits")
plt.ylabel("Time (sec)")
plt.plot(x,d,label="Divide and Conquer")
plt.plot(x,z,label="Karatsuba")
plt.plot(x,y, label="Grade School Multuplication")
plt.legend()
plt.show()
