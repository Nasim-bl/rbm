This project simulates the collective behavior of magnetic dipoles arranged in a 2D triangular lattice, influenced by dipole-dipole interactions, thermal noise, and external magnetic fields. It explores whether such systems can show phase transitions — a phenomenon traditionally considered impossible in 2D under short-range interactions.

🔍 Motivation
Magnetic nanostructures are used in memory devices, sensors, and bio-inspired navigation. We investigate whether their collective behavior can transition from disordered to ordered states — even when:

Each dipole is fixed in place but free to rotate in 3D.

The system is subject to thermal fluctuations and viscous forces.

Long-range dipolar interactions dominate (instead of standard short-range ones like in Ising/Heisenberg models).

🧪 Methods
Rotational Langevin Dynamics: Models the random rotation of dipoles due to temperature.

Molecular Dynamics (MD): Captures the time evolution of dipole orientations.

Triangular Lattice: Used to model fixed positions.

Periodic Boundary + Mean-Field: Prevents artificial edge effects due to long-range interactions.

📊 Key Parameters Measured
Magnetization ($m$): average orientation of dipoles

Susceptibility ($\chi$): response to magnetic field

Magnetic Energy ($u$)

Heat Capacity ($c$)

🌡️ Results
Without an external field:
A continuous phase transition occurs as temperature decreases — contradicting the Mermin-Wagner theorem thanks to long-range forces.

With external field:

In-plane fields (x/y) destroy the phase transition completely.

Out-of-plane field (z-direction) preserves the transition up to a critical strength.

Critical threshold in reduced units:
$\lambda_c^{-1} \approx 0.25$ (for spontaneous ordering)
Critical vertical field $B_z \approx 83.33$ (in reduced units)

🧬 Biological Insight
Inspired by magnetotactic bacteria and magnetic nanoparticles (MNPs) in animals, this model hints at how dipolar systems might act as biological magnetic sensors, possibly near a critical point to maximize sensitivity to weak geomagnetic fields.
