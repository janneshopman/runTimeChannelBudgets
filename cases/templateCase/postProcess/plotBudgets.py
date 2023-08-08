import numpy as np
import matplotlib.pyplot as plt

endTime = '60'

nu = 1/180

##### Plotting settings
plots = ['uxMean', 'uxRMS', 'uyRMS', 'uzRMS', 'uxpuypMean', 'k', 'prod', 'diss', 'trans', 'pDiff', 'vDiff']

titles = \
[ \
    "Mean stream-wise velocity", r"Root mean square $u_x$", r"Root mean square $u_y$", r"Root mean square $u_z$", r"Reynolds shear stress", \
    "Turbulent kinetic energy", "Production", "Dissipation", "Transport", "Pressure diffusion", "Viscous diffusion" \
]

yLabels = \
[ \
    r"$\overline{u_x}$", r"$u_{x,RMS}$", r"$u_{y,RMS}$", r"$u_{z,RMS}$", r"$\overline{u_x'u_y'}$", r"$k$", \
    r"$P_k$", r"$\epsilon_k$", r"$T_k$", r"$D^p_k$", r"$D^v_k$" \
]
    
###### Reference data
# Exctract [yPlus, uxMean, uxRMS, uyRMS, uzRMS, uxpuypMean, k]
basicData = np.loadtxt('refData/Chan180_S2a_basic_few.txt', skiprows = 36, usecols = (0, 1, 4, 5, 6, 8, 9))

# Extract [production, dissipation, transport, pressure diffusion, viscous diffusion]
RuuData = np.loadtxt('refData/Chan180_S2_budget_Ruu.txt', skiprows = 21, usecols = (1, 3, 4, 5, 6))
RvvData = np.loadtxt('refData/Chan180_S2_budget_Rvv.txt', skiprows = 21, usecols = (1, 3, 4, 5, 6))
RwwData = np.loadtxt('refData/Chan180_S2_budget_Rww.txt', skiprows = 21, usecols = (1, 3, 4, 5, 6))

# Combine data of u'u', v'v' and w'w' and scale (uTau = 0.9999, rounded to 1)
kData = 0.5*(RuuData + RvvData + RwwData)*nu

# Combine data to single array
refData = np.column_stack((basicData, kData))

###### Plot data  
for iPlot, plot in enumerate(plots):
    # Import run data
    dataFile = '../graphs/' + endTime + '/' + plot + '.xy'
    dataPoints = np.loadtxt(dataFile)

    # Scaling
    if plot == 'uxMean':
        uTau = np.sqrt(nu*dataPoints[0, 1]/dataPoints[0, 0])

    xScaling = nu/uTau

    if plot in ['uxMean', 'uxRMS', 'uyRMS', 'uzRMS']:
        yScaling = uTau
    elif plot in ['uxpuypMean', 'k']:
        yScaling = uTau**2
    elif plot in ['prod', 'diss', 'trans', 'pDiff', 'vDiff']:
        yScaling = uTau**4/nu

    # Plot run data    
    plt.figure(plot)
    plt.plot(dataPoints[:, 0]/xScaling, dataPoints[:, 1]/yScaling, label='solver')
 
    # Plot reference data
    plt.plot(refData[:, 0], refData[:, iPlot+1], '-k', label="Vreman")
    plt.title(titles[iPlot])
    plt.xlabel(r"$y^+$")
    plt.ylabel(yLabels[iPlot])
    plt.legend()
    plt.savefig('results/' + plot + '.png', bbox_inches='tight')
