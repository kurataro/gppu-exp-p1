#! /usr/bin/env python3

import matplotlib
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np

# Tuple csv filename
tuplefilename="outGPPU_nt_Edep.csv"

# output filename
outpufilename="figGPPU.jpg"

#gamma energy [MeV]
gammaenergy=0.25

data = pd.read_csv(tuplefilename, comment = '#', header=None)

fig = plt.figure(figsize=(8,6))
ax = fig.add_subplot(1,1,1)

#ax.grid(True)
n,bins,patches = ax.hist(data[1], bins=300,range=[0,3])

ax.set_yscale('log')
ax.set_xlabel("Gamma Energy Deposite [MeV]")
ax.set_ylim(1.0,1000000)

binindex=np.digitize(gammaenergy,bins)-1

print(n[binindex])

plt.savefig(outpufilename)
plt.show()
