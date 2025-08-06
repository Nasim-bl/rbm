This project simulates the collective behavior (dynamic) of a model including magnetic dipoles arranged in a 2D triangular lattice (Fig.?). 
In this model, dipoles are fixed in their position, but can rotate in 3D. 
They experience dipole interaction and thermal fluctuations, which create a rotational Brownian motion (RBM) at low Reynolds numbers. 
We compared the results in the absence and presence of (DC) external magnetic field. 

--- This project have 2 aims: 
1) To find an organized collective behaviour in the dynamics of this dipolar system.
   More advanced, we looked for a continuous phase transition of the system without an external magnetic field. 
   - To explore this, thermodynamic parameters such as magnetization $(m)$, susceptibility ($\chi$), magnetic energy ($u$), and heat capacity($c$) are studied. 
3) Finding out if this long-term ordering can last when the field is on.


---Results:  it vanishes when we applied B in-plane (xy-direction), while with the vertical component (z-direction), it was preserved(fig?). However, there exists a limit to this effect, naed as the "critical threshold range," which we identify by analyzing data across various lattice sizes. 
In other words, neither an external magnetic field nor thermal fluctuations can fully disrupt the ordering in this dipolar system, characterized by a continuous phase transition.

🔍 Motivation: 
Magnetic nanostructures, including thin films, are of great interest due to their unique properties at small scales; hence and understanding the dynamics of magnetic nanostructures is essential for optimizing their performance in both technological and biological contexts. 
Among the particles in these materials, there are long-range dipolar interactions, which create complexities that are not well addressed by conventional models, such as the Ising and Heisenberg models. 
These models, while effective for studying atomic-scale systems dominated by short-range exchange interactions, are insufficient for describing systems at the nanoscale or mesoscale, where long-range forces and anisotropic effects play a dominant role.
Dipolar interactions are fundamentally different from exchange interactions. 
Unlike the binary nature of exchange interactions (e.g., ±1 spins in the Ising model), dipolar interactions depend on the spatial orientation of the dipoles. 
For instance, head-to-tail alignment leads to attractive forces, while perpendicular alignment creates repulsion. 
This anisotropy makes dipolar systems inherently different from traditional models, even when long-range interactions are added as corrections. 
Furthermore, models based solely on exchange interactions fail to capture critical behaviors in the presence of external magnetic fields or thermal fluctuations, challenges that our approach seeks to address. 

Now in this project, we aim to study a nanostructure model that consists of these long-term dipole interactions but in 2D. 




🧪 Methods
Rotational Langevin Dynamics: Models the random rotation of dipoles due to temperature.

Molecular Dynamics (MD): Captures the time evolution of dipole orientations.

Periodic Boundary + Mean-Field: Prevents artificial edge effects due to long-range interactions.


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
