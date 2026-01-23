The file rbm contains the simulation codes developed for my MSc thesis “Rotational Brownian Dynamics of a System Consisting of Magnetic Dipoles”, supervised by https://github.com/mdniry
.
Here, I provide a summary of my work and its applications. Instructions on how to run the codes and their requirements are given in the How to run file.

# Summary: 
These codes simulate a magnetic system consisting of single-domain (SD) magnetic dipoles arranged on a two-dimensional (2D) triangular lattice. The dipoles are fixed in position but free to rotate in three dimensions (3D). They interact via long-range dipole–dipole interactions and are subjected to thermal fluctuations modeled as rotational Brownian motion (RBM, which gives the name of the main simulation code).
The primary goal of this work is to explore critical behavior in the collective dynamics of the system, specifically the existence of a continuous phase transition. According to the Mermin–Wagner theorem, such a transition cannot occur in a 2D system with short-range interactions. Here, we hypothesize that the long-range nature of dipolar interactions enables this transition. We find a continuous phase transition in the absence of an external magnetic field, showing that the dipoles remain ordered despite thermal noise (see results/no_magnetic_field). 
Next, we test the robustness of this critical behavior by applying a static external magnetic field. We find that any in-plane field (xy-direction) vanishes the phase transition by aligning the dipoles with the field. In contrast, a perpendicular field (z-direction) allows the transition to persist until the field reaches a critical threshold. This threshold is determined for different lattice sizes and extrapolated toward the thermodynamic limit (infinite system size). These results are provided in results/with_magnetic_field.

# Simulation Method: 
The simulations are performed using a Molecular Dynamics framework with Euler integration, allowing direct access to the time-dependent evolution of dipole configurations. Finite-size and boundary effects arising from long-range interactions are handled using periodic boundary conditions combined with a mean-field treatment.

# Applications
This simulation framework is relevant for studying magnetic nanostructures dominated by long-range and anisotropic interactions, such as dipole–dipole forces. Conventional models like the Ising or Heisenberg models are insufficient at the nano- or mesoscopic scale, where interaction strength depends strongly on dipole orientation and spatial configuration.
Dipolar interactions are inherently anisotropic: head-to-tail alignments are attractive, while perpendicular configurations are repulsive. These features lead to behaviors that cannot be captured by exchange-based models, especially in the presence of thermal noise or external magnetic fields.

# Numerical Challenges
Simulating dipolar systems presents several challenges:
1) Dipolar interactions are long-range, vectorial, and asymmetric.
2) In two dimensions, these interactions converge very slowly with distance, leading to strong finite-size and boundary effects.
If not handled carefully, boundary dipoles can introduce artificial asymmetries and spurious structures, such as vortex-like patterns similar to those seen in Berezinskii–Kosterlitz–Thouless–type transitions.
To address these issues, we combine periodic boundary conditions with a mean-field treatment of long-range interactions. This approach reduces edge effects and ensures physically consistent dynamics across the lattice. Further details are discussed in the model and boundary sections of the code.
