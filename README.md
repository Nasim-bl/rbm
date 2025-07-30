This project simulates the collective behaviour(dynamic) of a model within magnetic dipoles arranged in a 2D triangular lattice (fig?). 
In this model, dipoles are fixed in position, but can rotate in 3D. 
They experience dipole interaction and thermal fluctuations, which create a rotational Brownian motion (RBM) at low Reynolds numbers, and magnetic interaction is the external magnetic field is on. 

This project has 2 aims: 
1) finding the critical behaviour (phase transition) of the system when there is no magnetic field, through a continuous phase transition. 
   - To do this: we studied To explore this, we studeied key thermodynamic parameters such as magnetization, magnetic energy, susceptibility, and heat capacity. Well we found it!  (fig?)
2) Secondly, we wanted to know if this long-term ordering can last when the field is on. Well we found out, it vanishes when we applied B in-plane (xy-direction), while with the vertical component (z-direction), it was preserved(fig?). However, there exists a limit to this effect, naed as the "critical threshold range," which we identify by analyzing data across various lattice sizes. 
In other words, neither an external magnetic field nor thermal fluctuations can fully disrupt the ordering in this dipolar system, characterized by a continuous phase transition.

🔍 Motivation
Well, what are these results good for? 

- This finding contrasts with models like the Heisenberg model, where the Mermin-Wagner theorem prohibits such transitions due to the dominance of short-range interactions.



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
