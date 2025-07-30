# rbm

\documentclass[aps,prl,twocolumn,superscriptaddress,showpacs,preprintnumbers]{revtex4-2}

%BEGIN_FOLD % Packages
\usepackage{graphicx} % Package to include figures
\usepackage{xcolor} %For collered simbols
\usepackage{subcaption}
\usepackage{amsmath} % Package for mathematical symbols and environments
\usepackage{float}
\usepackage{amsfonts} % Additional mathematical fonts
\usepackage{amssymb} % Additional mathematical symbols
\usepackage{hyperref} % Package for hyperlinks
\usepackage{lipsum} % Package to generate dummy text, remove this in your actual paper
\usepackage{dsfont} %for blank 1
\usepackage{fouriernc}
\usepackage{bm}  %For making \mu, .. bold
\usepackage{epstopdf} 

%END_FOLD

\begin{document}
	
	%%%%%%% Abstract $ title %%%%%%% 
	
    %BEGIN_FOLD  Title, author, date	
	\title{The Wobbling of a Triangular Array of Magnetic Dipoles \\ 
		under the Influence of an External Magnetic Field}

	\author{F. Bolhasani}
	\email{f.bolhasani@iasbs.ac.ir}
	%\affiliation{Institute for Advanced Studies in Basic Sciences}
	
	\author{M. D. Niry}
	\email{m.d.niry@iasbs.ac.ir}
	\affiliation{Department of Physics, Institute for Advanced Studies in Basic Sciences, Zanjan, Iran}
	
    %END_FOLD  %\date{\today}
	
	\begin{abstract}
		
		Magnetic nanostructures have diverse technological applications, with their behavior being significantly influenced by long-range dipolar interactions. 
		This research studies the dynamics of a specific magnetic nanostructure using the Molecular Dynamics method. 
		The system comprises magnetic dipoles arranged in a fixed triangular 2D lattice, where the dipoles are restricted in position but free to rotate in three dimensions. 
		We also account for the effects of thermal fluctuations and model them using rotational Brownian motion at low Reynolds numbers.
		Our primary goal is to investigate whether this system shows critical behavior through a continuous phase transition.
		According to the Mermin-Wagner theorem, continuous phase transitions are typically impossible in 2D systems. 
		However, we hypothesize that the long-range dipolar interactions in our system could enable such a transition. 
		To explore this ordering in dipoles' collective behavior, we study key thermodynamic parameters such as magnetization, magnetic energy, susceptibility, and heat capacity, both with and without an external magnetic field. 
		Our findings indicate that a continuous phase transition occurs in the absence of an external magnetic field, confirming our hypothesis.
		In the following, we applied an external magnetic field and observed that its in-plane (xy-direction) component vanishes the phase transition while the vertical (z-direction) component allows it to persist.
		However, there exists a limit to this effect, referred to as the "critical threshold range," which we identify by analyzing data across various lattice sizes. 
		Our results demonstrate that neither an external magnetic field nor thermal fluctuations can fully disrupt the ordering in this dipolar system, characterized by a continuous phase transition. 
		This behavior can not be explained by conventional models, such as the Heisenberg model used to describe magnetic materials. 
		\\
		\\\textit{keywords: dipolar interaction, long-range interaction, rotational Langevin dynamics} 
		
	\end{abstract}
	
	%BEGIN_FOLD  maketitle
	\pacs{}
	
	\maketitle % Prints the title, author, and date
	%END_FOLD 
	
	%%%%%%%%  Document %%%%%%%%
	
	\section{Introduction}
	
	%BEGIN_FOLD  1st p
	
	Magnetic nanostructures, including thin films, are of great interest due to their unique properties at small scales, such as superparamagnetism and enhanced surface effects \cite{Shukla2013}. 
	These properties make them critical for various applications, including data storage (e.g., hard drives and MRAM), advanced sensors (e.g., magnetoresistive sensors), and spintronics \cite{Constantinescu2023, Aich2023}. 
	Advances in atomic-scale engineering have further enabled the fabrication of magnetic thin films and nanoparticle assemblies, where long-range interactions significantly influence behavior \cite{Mohamed2019}.
	   
	%END_FOLD
	
	%BEGIN_FOLD  2d p
	 
	Understanding the dynamics and critical behavior of magnetic nanostructures is essential for optimizing their performance in both technological and biological contexts. 
	In particular, the long-range dipolar interactions in these systems introduce complexities that are not well-addressed by conventional models, such as the Ising and Heisenberg models. 
	These models, while effective for studying atomic-scale systems dominated by short-range exchange interactions, are insufficient for describing systems at the nanoscale or mesoscale, where long-range forces and anisotropic effects play a dominant role.
	
	%END_FOLD 
	
	%BEGIN_FOLD  3d p
	
	Dipolar interactions are fundamentally different from exchange interactions. Unlike the binary nature of exchange interactions (e.g., $\pm 1$ spins in the Ising model), dipolar interactions depend on the spatial orientation of the dipoles. 
	For instance, head-to-tail alignment leads to attractive forces, while perpendicular alignment creates repulsion. 
	This anisotropy makes dipolar systems inherently different from traditional models, even when long-range interactions are added as corrections \cite{Tissa}. 
	Furthermore, models based solely on exchange interactions fail to capture critical behaviors in the presence of external magnetic fields or thermal fluctuations, challenges that our approach seeks to address.
	
	%END_FOLD
	
	%BEGIN_FOLD  4th p
	
	Our nanostructure model consists of single-domain (SD) magnetic dipoles arranged in a triangular Bravais lattice. 
	These dipoles are fixed in a 2D lattice but can freely rotate in three dimensions, resulting in rotational dynamics. 
	The dynamics of their magnetic moments are described by the kinematic equation \eqref{eq: 1-a}, coupled with the Rotational Langevin equation under low-Reynolds-number conditions. 
	This formulation allows us to study the interplay between deterministic torques and thermal fluctuations, providing a powerful framework for exploring critical behavior and phase transitions \cite{Coffey2004}. 
	Notably, the Mermin-Wagner theorem \cite{Hohenberg1967}, which typically forbids phase transitions in 2D systems, does not apply here because our model explicitly includes long-range dipolar interactions.
	
	%END_FOLD
	
	%BEGIN_FOLD  5th p 
	
	Our nanostructure model consists of single-domain (SD) magnetic dipoles arranged in a triangular Bravais lattice. 
	These dipoles are fixed in a 2D lattice but can freely rotate in three dimensions, resulting in rotational dynamics. 
	The dynamics of their magnetic moments are described by the kinematic equation \eqref{eq: 1-a}, coupled with the Rotational Langevin equation under low-Reynolds-number conditions. 
	This formulation allows us to study the interplay between deterministic torques and thermal fluctuations, providing a powerful framework for exploring critical behavior and phase transitions \cite{Coffey2004}. 
	Notably, the Mermin-Wagner theorem \cite{Hohenberg1967}, which typically forbids phase transitions in 2D systems, does not apply here because our model explicitly includes long-range dipolar interactions.
	
	%END_FOLD
	
	%BEGIN_FOLD  6th p
	
	Exploring the dipolar has challenges, as the interactions are asymmetrical and vector. 
	Additionally, the long-range nature of dipolar interaction can significantly leads to the edge effect for finite sizes. 
	The dipolar interactions between one dipole to others in two dimensional (2D) converge very slowly with respect to their distance. 
	Therefore, if proper accuracy and considerations are not considered, the dipoles located in the boundary can create asymmetrically to the dynamics of the system. 
	This raises the  possibility of creating the artificial emergence of vortices similar to those observed in the phase transition of Berezinskii–Kosterlitz–Thouless (BKT) \cite {Giachetti2022}.
	To tackle the finite size issue, we consider a combination of periodic boundary condition and Mean-Field theory that eliminates these complications for the boundary condition in our system (refer to model section). 
	We will explain this issue and our solution for it in more detail in the boundary section. 
	
	%END_FOLD 	
	
	%BEGIN_FOLD  7th p 
	
	For numerical simulations, we employ the Euler method within a Molecular Dynamics (MD) framework, focusing exclusively on the rotational motion of the dipoles. 
	Unlike Monte Carlo (MC) methods, which are primarily suited for equilibrium studies in models such as Ising or Heisenberg, MD enables the analysis of the time-dependent evolution of dipole configurations.
	This makes MD a more appropriate choice for studying the dynamic properties of our dipolar systems, which is the primary objective of this research.
	While the Monte Carlo method is a viable alternative, especially for larger systems due to its scalability, it lacks the ability to capture the temporal evolution of dipole configurations. 
	This limitation renders it unsuitable for our study of dynamic behavior. 
	An additional advantage of MD is its ability to generate independent realizations; each simulation run provides a unique and statistically independent instance of the system’s behavior over time. 
	This capability is crucial for robust analysis and accurate characterization of the system’s dynamics.

	
	%END_FOLD

    %BEGIN_FOLD  8th p
	 
	In the following sections, we introduce the model and the mathematical foundations necessary for our analysis. 
	We then convert these equations into a reduced units system. 
	We then present a reduced unit system for the equations, describe the thermodynamic parameters used to characterize critical behavior, and explore the system’s response to external magnetic fields. 
	Finally, we discuss our results, including the biological implications of dipolar systems, and conclude with insights into the broader relevance of our findings.
	
	%END_FOLD
	
	\section{Model and Method}
	
	%BEGIN_FOLD  1st Paragrpah 
	
	In our proposed model, nanomagnetic dipoles are organized in a triangular Bravis lattice with a fixed inter-dipole distance of $l$ (Fig.~\ref{fig 1}). 
	Each dipole is considered as a sphere with a radios of $a$ and a consistent magnetic moment of magnetite $\mu$.
	The dynamic behavior of a single dipole (indexed as $i$) is given by the following coupled equations: 
		%
		%%%%% eq: 1-a, eq: 1-b. coupled_equations%%%%% 
		\begin{align*}
		\dot{\bm\othermu}_i (t) & = 
		\bm\otheromega_i (t) \times\bm\othermu_i (t) \tag{1a}\label{eq: 1-a} \text{,}\\ 
		I\dot{\bm\otheromega}_i (t) + \zeta \bm\otheromega_i (t) & = 
		\mathbf W_i (t) + \bm\othermu_i (t) \times \mathbf B_i(t)  \tag{1b} \text{.}\label{eq: 1-b}  
		\end{align*}
		% 
		% 
		%%%%% fig: 1 (latttice configuaration) %%%%%
		\begin{figure}[t]
		\includegraphics[width=0.3\textwidth]{1.eps}
		\captionsetup{font=footnotesize, justification=raggedright}
			\caption{
			(Color online)
			The configuration of nine dipoles within a triangular lattice.  
			Positions of the dipoles in the lattice are represented by the solid circles $(\bullet)$, while thin arrows $(\textcolor{red}\rightarrow)$ indicate the magnetic moment of dipoles either inside or outside the lattice plane, which is not appeared here. 
			The primitive lattice basis vectors, denoted by $\mathbf{a}$ and $\mathbf{b}$, are shown by the thick arrows $\textcolor{green}{\bm\rightarrow}$.
			The solid lines, around the southern east dipole,  shows the unit cell and the gray region indicates the supercell. 
			} \label{fig 1}
		\end{figure}
		%
		%
	Kinematic Eq.~\eqref{eq: 1-a} describes the time evolution of the magnetic moment $\mu_i$, which is influenced by the angular momentum $\bm{\otheromega}_i$. 
	Here, the dot indicates the time derivative.  
	Conversely, Eq.~\eqref{eq: 1-b}, known as the Euler-Langevin equation, describes the temporal evolution of the angular momentum $(I\dot{\bm\otheromega}_i)$. 
	Torques influence this evolution due to viscosity $(\zeta \bm\otheromega_i)$, thermal fluctuations $\mathbf W_i$, and magnetic interaction $(\bm\othermu_i \times \mathbf B_i)$. 
	In this context, $I$ represents the moment of inertia, while dissipation coefficient, $\zeta$, is determined as $\zeta = 8 \pi a^3 \eta$. 
	The viscosity coefficient $\eta$ corresponds to the dynamic viscosity. %of water $0.65  \mathrm{mPa.s}$ at the body temperature. 
	Furthermore, $\mathbf W_i$ represents a white noise vector that follows a Gaussian distribution, with its correlation function denoted as 
		%
		%%%%% eq: 2, white noise %%%%
		\begin{align*} \label{eq: 2}
		\langle W_{ip}(t) \, W_{jq}(t') \rangle & = 2k_{\mathrm B} T \zeta \delta_{ij} \delta_{pq} \delta(t - t') \text{.}
		\tag{2}
		\end{align*}
		%
		%
	Here, $\langle ... \rangle$ indicates the ensemble average, $i \text{and} j$ are the index of two separate dipoles, and $p, q = 1, 2, 3 $ corresponds to the Cartesian axes (i.e., $ W_{ip} = \mathbf W_i \cdot \hat{\mathbf e}_p$). 
	Lastly, the term $\bm\othermu_i (t) \times \mathbf B_i(t)$ describes the torque exerted on the dipoles by the total magnetic field 
		% 
		%%%% eq: 3, Magnetic field %%%%
		\begin{align*} \label{eq: 3}
		\mathbf B_i(t) & = 
		\mathbf B_{\text{ext}} + \frac{\mu_0 \mu}{4\pi} \sum_{j \neq i}^N \overleftrightarrow{\mathbf{J}}(\mathbf r_{ij}) \cdot \hat{\bm{\othermu}}_j(t) \text{.}
		\tag{3}
		\end{align*}
		%
		% 
	In this context, $\mathbf B_{\text{ext}}$ represents the external magnetic field. 
	The second term accounts for the induced magnetic field from neighboring dipoles surrounding the $i^{\text{th}}$ dipole. 
	Here, $\mu_0$ denotes the magnetic permeability of free space, and $\overleftrightarrow{\mathbf{J}}(\mathbf r_{ij})$ represents the dipolar coupling tensor between two dipoles\cite{Khoddam2018}, defined by  
		% 
		%%%% eq: 4, J_copling tensor %%%%
		\begin{align*} \label{eq: 4}
		 \overleftrightarrow{\mathbf{J}}(\mathbf r_{ij}) & =
		 \frac{{3\hat{\mathbf r}_{ij} \hat{\mathbf r}_{ij} - \mathds{1}}}{{\lvert \mathbf{r}_{ij} \rvert^3}} \text{.}
		\tag{4}
		\end{align*}
		%
		%
	Here, the dyadic product $\hat{\mathbf r}_{ij} \hat{\mathbf r}_{ij}$ is a mathematical operation  involving two vectors, and $\mathds{1}$ shows the rank-$2$ identity matrix in three dimensions.  
	Lastly, the vector $\mathbf r_{ij} := \mathbf r_i - \mathbf r_j$ represents the relative distance between two dipoles ($i$ and $j$), but it can be defined for any couples. 
	
	%END_FOLD
	
	%BEGIN_FOLD  2d Paragraph
	
	Finally, as Eq.~\eqref{eq: 3} indicates, the magnetic energy associated with the $i^{\mathrm {th}}$ dipole derives from 
	%
		%%%%% eq: 5, magnetic energy %%%% 
		\begin{align*} \label{eq: 5}
		U_i(t) & = -\bm\othermu_i(t) \cdot \mathbf B_i(t) \text{.}\tag{5}
	\end{align*}
		%

	%END_FOLD
	
	\subsection{a. Reduced Unit System}
	
	%BEGIN_FOLD  1st Paragraph
	
	To simplify the equations and eliminate units, we convert them into a reduced unit system. Then, in this framework, the temporal evolution of $\bm\othermu$ in low-Reynolds-number is written as 
		%  
		%%%% eq: 6, uniqe equation, dipole's dynamics %%%%%
		\begin{align*}\label{eq: 6}
		\dot{\bm\othermu}_i (t)& = 
		\mathbf W_i (t) \times 
		\bm\othermu_i (t) + 
		\frac{1}{2} \big[\bm\othermu_i (t) \times  \mathbf B_i(t)\big] \times \bm\othermu_i (t) \text{,}
		\tag{6} 
		\end{align*}
		%
		%
	which is derived by combining Eq.~\eqref{eq: 1-a} and \eqref{eq: 1-b}. 
	Here, the term associated with the moment of inertia in Eq.~\eqref{eq: 1-b} is considered negligible due to the assumption of the low-Reynolds-number regime.
	Next, the total magnetic field in Eq.~\eqref{eq: 3} is transformed into 
		% 
		%%%% eq: 7, magnetic field in reduced unit system %%%%
		\begin{align*}\label{eq: 7}
		\mathbf B_i(t)
		 & = 
		 \mathbf B_{\text{ext}} + \beta \Lambda \sum_{j \neq i}^N \overleftrightarrow{\mathbf{J}}(\mathbf r_{ij}) \cdot \hat{\bm{\othermu}}_j(t) \text{,}
		\tag{7}
		\end{align*}
		%
		%
	with the dimensionless parameter $\lambda = \beta\Lambda$ indicating the strength of the magnetic interaction $(\Lambda = \frac{{\mu_0 \mu^2}}{{4\pi l^3}})$ relative to thermal fluctuations, $\beta^{-1} = k_{\text{B}} T $.  
	
	%END_FOLD
	
	%BEGIN_FOLD  2d Paragraph
	
	In our simulations, $\lambda^{-1}$ is the control parameter used to observe the system relative to it.  
	This parameter can be increased by either raising the dipole density $l^{-3}$, or lowering the temperature $T$. 
	
	%END_FOLD
	
	%BEGIN_FOLD 3d Paragraph 
	
	Lastly, to calculate the reduced magnetic energy, we substitute Eq.~\eqref{eq: 7} into Eq.~\eqref{eq: 5}. 
	It should be noticed that the form of Eqs.~\eqref{eq: 4} and ~\eqref{eq: 5} do not vary in the reduced unit system. 
	
	%END_FOLD
	 
	\subsection{b. Boundary Condition} 
	
	%BEGIN_FOLD  1st Paragraph
		
		%%%% fig: 2, boundary configuaration %%%%
		\begin{figure}[t] 
			\includegraphics[width=0.37\textwidth]{2.eps} 
			\captionsetup{font=footnotesize, justification=raggedright}
			\caption{
				A schematic representation of the periodic boundary condition with the main unit suppercell indexed $(0, 0)$ containing nine dipoles (see Fig.~\ref{fig 1}). 
				Copies of this supercell fill its surrounding within a circle of radius $R$. 
				In this representation, $i$ and $j$ denote dipoles within the primary super cell, while $j^{\prime}$ represents a dipole in the periodic boundary. 
				The empty circles $(\circ)$ depict the dipole $j^{\prime}$ in the adjacent cell. 
				The vector $\mathbf{r}_{ij}$ denotes the relative distance between dipoles within the main supercell, while $\mathbf{r}_{ij^{\prime}} = \mathbf{r}_{ij} + \mathbf R_{m, n}$ connects dipole $i$ in the main supercell to dipole $j^{\prime}$ in the adjacent supercell. 
			} \label{fig 2}
		\end{figure}
		%%
		%
	To avoid artificial ordered configurations, we initialize the dipoles with random orientations, ensuring that the average of the initial directions at $t=0$ is approximately zero. 
	However, more than this approach is required for simulating finite-size configurations, as we must account for edge effects. 
	These effects can lead to artificial ordering, similar to the vortex observed in Berezinskii-Kosterlitz-Thouless (BKT) transition.
	Additionally, the long-range nature of the dipolar interaction in our system means it does not diminish even at large distances. 
	
	%END_FOLD
	
	%BEGIN_FOLD  2d Paragraph
	
	To address these issues, we implement a unique boundary condition. 
	We divide the dipolar interaction into three distinct groups: 
	(1) The internal interaction among the dipoles within the main supercell  (Fig~\ref{fig 1}), as discussed in the previous sections. 
	(2) The interaction between the dipoles within the main supercell and the neighboring dipoles up to a radius of $R$, using a periodic boundary condition  (Fig~\ref{fig 2}). 
	(3) The interaction between the dipoles within the main supercell and those beyond the radius $R$, which derives from the Mean-Field assumption.
	
	%END_FOLD
	
	%BEGIN_FOLD  3d Paragraph
	
	To implement periodic boundary conditions, we replicate the main supercell, indexed as $(0, 0)$, until the radius $R$ is reached. 
	Here, we create the adjacent supercells indexed as $(m, n)$ appearing in Fig.~\ref{fig 2}.   
	In our simulation, $R = 500 |\mathbf a|$, or when the strength of the magnetic interaction $U \propto 1/R^3$ becomes approximately to $10^{-8}$ in the reduced unit system. 
	Subsequently, we derive the magnetic field contribution from the adjacent cells acting on the $i^{\mathrm{th}}$ dipole in the main supercell, resulting in  
		%
		%%%%% eq: 8, magnetic field, periodic boundary condition %%%%%
		\begin{align*}\label{eq: 8}
		\mathbf B_i(t) 
		& = 
		\mathbf B_{\text{ext}} 
		+ 
		\beta \Lambda \sum_{(m, n)}^{<R} 
		\:
		\sum_{j=1}^{\:\:\:N\:\:\prime} 
		~
		\overleftrightarrow{\mathbf{J}}(\mathbf r_{ij} + 	\mathbf R_{m, n}) \cdot \hat{\bm{\othermu}}_j(t) 
		\text{, }
		\tag{8}
	\end{align*}
		% 
		%
	as the extension of   Eq.~\eqref{eq: 7}.  
	Here, the second summation $\sum^{\prime}$ simplifies as $\sum_{j \neq i}$ where $(m, n) = (0, 0)$, and the vector $\mathbf R_{m, n}$  represents the relative position vector from the center of the main supercell to its neighbors. 
	If the interactions are only in the main supercell, then $\mathbf R_{0, 0} = 0$. 
	We limit the summation to within the radius $R$ as it is impractical to sum to infinity, leading to the consideration of the following interaction part. 
	 
	%END_FOLD
	
	%BEGIN_FOLD  4th Paragraph
	
	As mentioned, the dipolar interaction does not diminish significantly, even at large distances. 
	However, applying boundary conditions beyond $R = 500 |\mathbf a|$ up to infinity is impractical. 
	Therefore, interactions beyond this range must be accounted for, which our model addresses using the mean-field assumption. 
	To do so, we consider the effect of the average dipole moment $\mathbf m (t) = \frac{1}{N}\sum_{i=1}^N \bm\othermu_i (t)$ on the main supercell $(0, 0)$. 
	This $m$, later called magnetization, is derived from the main supercell and represents the contributions from dipoles located beyond $R$ in our model. 
	
	%END_FOLD
	
	%BEGIN_FOLD  5th Paragraph
	
		%
		%%%%% fig: 3, J (\infty) %%%%
		\begin{figure} 
		\includegraphics[width=0.48\textwidth]{3.eps} 
		\captionsetup{font=footnotesize, justification=raggedright}
		\caption{ 
			The linear fit (solid line) of the coupling coefficient $A(d)$ for different radii $(d)$ extracted from solid circles ($\bullet$) versus the  $1/d$, with the intercept $A(\infty) = 5.52$. 
		} \label{fig 3}
		\end{figure}
		%
		%
	We incorporate the remained magnetic field derived from the mean-field assumption, given by $\mathbf B_{\text{MF}, i} = \big[ \overleftrightarrow{\mathbf{J}} (\infty) - \overleftrightarrow{\mathbf{J}} (R) \big] \cdot~\mathbf m$ into the total magnetic field in Eq.~\eqref{eq: 8}. 
	Here, $\overleftrightarrow{\mathbf{J}} (R) = \sum_{(m,n) < R} \sum_{j=1}^{\prime ~ N} \overleftrightarrow{\mathbf{J}}(\mathbf r_{ij})$ represents the coupling tensor between the dipoles in the main supercell and those in the surrounding region up to the radius $R$, as accounted for in the periodic boundary condition. 
	However, computing $\overleftrightarrow{\mathbf{J}} (\infty)$ is impractical due to its asymmetry and the computational cost of summing to an infinite radius. 
	To tackle this issue, we include a numerical approach, in which we compute the coupling tensor for various radii and then, by using extrapolation we estimate the amount of $\overleftrightarrow{\mathbf{J}} (\infty)$.
	
	%END_FOLD 
	
	%BEGIN_FOLD  6th Paragraph
	 
	First, we provide an analytical method for estimating  $\overleftrightarrow{\mathbf{J}}(\infty)$, and then present our approach.    
	We begin by converting the summation $\sum_{(m,n)\leq r} \sum_{j=1}^{\prime ~ N}$, which contributes to  $\overleftrightarrow{\mathbf{J}}(r)$, into a polar integral $\sigma \int_{l}^{r} \int_{0}^{2\pi} r \, \mathrm d r \, \mathrm d\phi$. 
	Here, $\sigma$ represents the number density of dipoles in the lattice plane, and $l$ denotes the minimum distance between two dipoles, preventing spatial overlap.   
	$\overleftrightarrow{\mathbf{J}}(r)$ is a $3 \times 3$ tensor, and due to the homogeneous symmetry of the system, the non-diagonal elements become zero. 
	This results in the expression 
		%
		%%%%% eq: 9,  J matrix %%%%%
		\begin{align*} \label{eq: 9}
		\overleftrightarrow{\mathbf{J}}(r) = A (r) \left( \begin{array}{ccc} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & -2 \end{array} \right) 
		\tag{9} \text{,}
		\end{align*} 
		%
		%
	where $A$ is proportional to $1 / r$.   
	This calculation assumes the lattice is isotropic and homogeneous, with continuous rotational and translational symmetry. 
	However, our numerical simulation offers a more accurate estimation of $A(r)$ for a triangular lattice, as illustrated in Fig~\ref{fig 3}.
	In plotting this graph, the dependency of $A$ on $1/r$ is used, giving a linear behavior. 
	By extrapolating at $r\rightarrow \infty$, we estimate the value of $5.52$. 
	
	%END_FOLD
	
	%BEGIN_FOLD  7th Paragraph 
	 
	Finally, considering the effect of boundary conditions on the main supercell, the total magnetic field
		%
		%%%%% eq: 10, total magnetic field + boundary codition %%%%% 
		\begin{align*}\label{eq: 10}
		\mathbf B_i(t) 
		& = 
		\mathbf B_{\text{ext}} 
		+ 
		\beta \Lambda \sum_{(m, n)}^{<R} \sum_{j = 1}^{~~ N ~\prime}  \overleftrightarrow{\mathbf{J}}(\mathbf r_{ij} + \mathbf R_{m, n}) \cdot  \hat{\bm{\othermu}}_j(t) 
		&\\&
		+ 
		\big[ \overleftrightarrow{\mathbf{J}} (\infty) - \overleftrightarrow{\mathbf{J}} (R) \big] \cdot \mathbf m (t)
		\tag{10} 
		\end{align*}
		% 
		%
	is derived. 
	Here, the first term represents the external magnetic field, the second term accounts for the interaction of dipoles up to radius $R$, and the final term describes the effect of dipoles beyond radius $R$ using the mean-field assumption. 
	
	%END_FOLD
	
	\subsection{c. Some Thermodynamic Quantities}\label{model: thermo}
	
	%BEGIN_FOLD  1st Paragraph
	
	The dynamics of a single dipole can be described by a set of equations that we have derived. 
	However, our primary focus is on observing the collective behavior of the dipoles and identifying any critical phenomena. 
	To analyze this, we examine standard thermodynamic parameters such as magnetization, susceptibility, magnetic energy, and heat capacity. 
	
	%END_FOLD
	
	%BEGIN_FOLD  2d Paragraph
	
	The first parameter is magnetization, $\mathbf M (t) = \sum_{i=1}^{N} \bm\othermu_i(t)$, which is a vector derived from the sum of the magnetic moments of all dipoles at a given time $t$.
	Here, $N$ represents the total number of dipoles in the lattice. 
	In our model, however, we focus on the magnitude of this parameter.
	To standardize our calculations, we introduce a normalized version called the density of the magnitude of magnetization, denoted as $m(t) = M (t)/N$. 
	Although $m$ is typically considered the order parameter in magnetic systems, our results will demonstrate that the magnitude of magnetization in the lattice plane direction $m_p$ serves as the order parameter in our system.
	
	%END_FOLD
	
	%BEGIN_FOLD  3d Paragraph

	Susceptibility, denoted as $\chi$, is an essential parameter in magnetic systems undergoing continuous phase transition. 
	It is defined as  $\left(\frac{\partial M}{\partial h}\right)_T$, where $h$ represents the external magnetic field. 
	However, in practical applications, round-off errors can arise when dealing with subtract numbers of similar magnitude.
	To address this issue, an alternative expression for susceptibility is used: $\chi = \beta \left (\langle M^2 \rangle - \langle M \rangle^2 \right)$ \cite{Giordano2012}, which accounts for the influence of thermal fluctuations on the magnetic moment. 
	In our system, the density of susceptibility is denoted as 
	%
	%%%%% eq: 11, Density of susceptibility %%%%
	\begin{align*} \label {eq: 11}
		\frac{\chi}{N} &= 
		\frac{N \lambda}{\Lambda} \left( \langle m^2 \rangle - \langle m \rangle^2 \right) \text{,}
		\tag{11}
	\end{align*}
	%
	%
	with $\beta$ replaced by  $\lambda/\Lambda$. 
	
	%END_FOLD
	
	%BEGIN_FOLD  4th Paragraph
	
	Previously, we derived the magnetic energy exerted on a single dipole in Eq.~\eqref{eq: 5}. 
	Now, the density of the total magnetic energy drives from $u_{\text{tot}} = U_\text{tot}/N$, where $U_{\text{tot}} = \sum_{i=1}^{N} U_{\text{tot}, i}(t)$ is the total magnetic energy of the system. 
	
	%END_FOLD
	
	%BEGIN_FOLD  5th Paragraph
	
	Lastly, the heat capacity is derived change in magnetic energy with respect to temperature, $\left( \frac{\partial U_{\text{tot}}}{\partial T} \right)_{V}$. 
	Similarly, to minimize errors alike to those encountered with susceptibility, the formula  $C = k_{\text B} \beta^2 \left( \langle U_{\text{tot}}^2 \rangle - \langle U_{\text{tot}} \rangle^2 \right)$ is used  \cite{Giordano2012}. 
	The specific heat capacity is then defined by 
	%
	%%%%% eq: 12, Heat capacity %%%%%
	\begin{align*} \label{eq: 12}
		c &= 
		\frac{N  k_{\text B} \lambda^2}{\Lambda^2} \left( \langle u_{\text{tot}}^2 \rangle - \langle u_{\text{tot}} \rangle^2 \right) \text{.}
		\tag{12}
	\end{align*}
	%
	%
	Peaks in susceptibility and heat capacity are commonly used to identify the critical point at which order emerges in the system (see Fig.~\ref{fig: 4-a} and \ref{fig: 4-b}). 
	
	%END_FOLD
	
	\section{Results}\label{sec: results}
	%
	%BEGIN_FOLD  1st paragraph
		%
		%
		%%%%% fig: 4-a & fig: 4-b (m-\chi, E-c) %%%%
		\begin{figure*}[tbp]
		\centering
		\subfloat[]{\includegraphics[width=0.45\textwidth]{4a.eps}\label{fig: 4-a}}
	    \hfill
		\subfloat[]{\includegraphics[width=0.43\textwidth]{4b.eps}\label{fig: 4-b}}
		\hfill
		\\[-0.2cm]
		\captionsetup{font=footnotesize, justification=raggedright}
		\caption{
		(a) The inset shows the magnetization $\langle m \rangle$, while the main plot presents susceptibility $\chi/N$ as a function of the control parameter.  
		(b) The inset depicts the magnetic energy $\langle u \rangle$, and the main plot illustrates the specific heat capacity $c$.  
		In both diagrams, the horizontal axis represents the control parameter. 
		The analysis covers lattice sizes ranging from $N = 100$ to $2025$, with ensemble averages calculated from $500$ realizations. 
		For the main plots, data are shown every $12$ steps, while in the insets, data are shown every $20$ steps for clarity. 
		The peaks in the main figure correspond to the clearer representation of inflection points in the inset, defining the critical point for each lattice sizes. 
		}
	\end{figure*}
		% 
		%
	Our objective is to investigate the collective behavior of our system under the influence of both the presence and absence of a static external magnetic field. 
	To achieve this, we vary the control parameter, $\lambda^{-1} = (\beta\Lambda)^{-1}$, and observe the system's evolution using the thermodynamic parameters described in previous section. 
	We then aggregate multiple realizations and calculate the ensemble average to analyze the results. 
		%
		%%%%% fig: 5-a & fig: 5-b, critical point estimation-suscebtibility power like behaviour %%%
		\begin{figure*}[tbp]
		\centering
		\subfloat[]{\includegraphics[width=0.49\textwidth]{5a.eps}\label{fig: 5-a}}
		\captionsetup{font=footnotesize, justification=raggedright}
		\hfill
		\subfloat[]{\includegraphics[width=0.49\textwidth]{5b.eps}\label{fig: 5-b}}
		\\[-0.2cm]
		\captionsetup{font=footnotesize, justification=raggedright}
		\caption{
		(a) The inset shows estimates of the critical point $(1/\lambda_{\text{c}})$ from susceptibility and heat capacity peaks, plotted against $(\log N)^{-1}$.
		(b) The main plot displays the power-law behavior of susceptibility peaks $(\chi_{\text{max}})$ with an exponent of $2.4$, as a function of lattice dimension $L$, for sizes ranging from $10 \times 10$ to $45 \times 45$.
		}
		\end{figure*} 
		%
	
	%END_FOLD
	
	\subsection {a. Absence of External Magnetic Field}

	%BEGIN_FOLD  1st Paragraph
	
	The inset of Fig.~\ref{fig: 4-a} shows the ensemble average of the magnetization density $\langle m \rangle$ as a function of the control parameter for different triangular lattice sizes, with the external magnetic field set to zero ($\mathbf B_{\text{ext}} = 0$). 
	At high reduced temperatures, $\langle m \rangle$ approaches zero, and as $(\beta\Lambda)^{-1}$ decreases, it increases, reaching its maximum value around $\langle m \rangle \sim 1$.  
	This behavior indicates a continuous phase transition with $\langle m \rangle$ as the order parameter.  
	However, in our model, the actual order parameter is its projection in the lattice plane, $m_{\mathrm p}$, as shown in Fig.~\ref{fig: 6-b}. 
	The non-zero $\langle m \rangle$ value at high $(\beta\Lambda)^{-1}$ is due to thermal fluctuations and the norm's nature. 
	This effect diminishes in larger lattices (e.g., $N \geq 1600$). 
	Notably, an inflection point on each curve shifts backward with increasing lattice size, indicating that a smaller control parameter is needed to induce order, as highlighted in the main figure.  
	
	%END_FOLD
	
	%BEGIN_FOLD  2d paragraph 
	
	The main diagram in Fig.~\ref{fig: 4-a} displays the susceptibility $\chi/N$, plotted against the reduced temperature. 
	This diagram clearly shows the inflections and their movement, hidden in the inset, to the left. 
	Peaks in the susceptibility occur because of the divergence of the derivative of the magnetization with respect to the external magnetic field, or, equivalently, when there is a significant difference between the first and second moments of the magnetization, as described in Eq.~\eqref{eq: 11}. 
	These peaks indicate spontaneous symmetry breaking at the critical point $({\lambda_\text{c}}^{-1})$. 
	
	%END_FOLD
	
	%BEGIN_FOLD  3d Paragraph 
	
	The inner diagram of Fig.~\ref{fig: 4-b} shows the density of the total magnetic energy $\langle u_{\text{tot}} \rangle$.
	Similar to magnetization, changes in the slope around the inflection points indicate the presence of a continuous phase transition.
	
	%END_FOLD
	
	%BEGIN_FOLD  4th Paragraph
	
	The main diagram in Fig.~\ref{fig: 4-b} illustrates the specific heat capacity, denoted as $c$. 
	Peaks in this diagram correspond to critical points where the difference between $\langle u_{\text{tot}}^2 \rangle$ and $\langle u_{\text{tot}} \rangle^2$ becomes significant, reflecting the behavior observed in susceptibility.
	
	%END_FOLD
	
	%BEGIN_FOLD  5th paragraph
	
	Fig.~\ref{fig: 5-a} illustrates the linear regression of the critical point $(\lambda_\text c)^{-1}$ extracted from the peaks of the diagrams in Fig.~\ref{fig: 4-a} and \ref{fig: 4-b} plotted against the reciprocal of the logarithm of dipole numbers $(\log N)^{-1}$. 
	The main graph indicates that susceptibility peaks follow $(\lambda_{\text{c}})^{-1} = 0.95 / \log N + 0.25$, with an intercept of $0.25 \pm 0.01$. 
	The inset reveals that specific heat capacity peaks follow $(\lambda_{\text{c}})^{-1} = 0.72 / \log N + 0.33$, with an intercept of $0.33 \pm 0.02$. 
	Although similar functions were expected for both quantities, the slight intercept discrepancy is attributed to computational inaccuracies and the system's pseudo-critical behavior \cite{Landau1976}.
	
	%END_FOLD
	
	%BEGIN_FOLD  5th Paragraph
	
	Fig.~\ref{fig: 5-b} shows a log-log plot of the susceptibility peaks, $\chi_{\text{max}}$, as a function of lattice length ($L$), indicating a power-law behavior with an exponent of $\alpha = 2.4$. 
	We did not include a corresponding plot for the peak of specific heat capacity versus $L$ due to the need for larger lattice sizes to determine whether the behavior follows a logarithmic or power-law trend. 
	In the thermodynamic limit, however, ($N \to \infty$), it is anticipated that both susceptibility and specific heat capacity are expected to diverge, accompanied by an increase in correlation length.
	
		%%% fig: 6-a & fig: 6-b, magnetization with the presence of B - and hystersis) 	 
		\begin{figure*}[tbp]
		\centering
		\subfloat[]{\includegraphics[width=0.45\textwidth]{6a.eps}\label{fig: 6-a}}
		\hfill
		\subfloat[]{\includegraphics[width=0.44\textwidth]
			{6b.eps}\label{fig: 6-b}}
		\captionsetup{font=footnotesize, justification=raggedright}
		\caption{
		(a) The hysteresis diagram for a lattice with $400$ dipoles. 
		The vertical axis represents the $x$-component of magnetization $\langle m_x \rangle$, while the horizontal axis denotes the external magnetic field along the $x$-axis ($B_x$). 
		The arrows labeled $1$, $2$, and $3$ indicate the direction of the hysteresis loop, starting from the solid red circle ($\color{red} \bullet$). 
		The parameters $m_\text{r}$ and $b_\text{c}$ represent the remanent magnetization and coercive field, respectively. 
		The initial orientation of the dipoles is random, and the system is considered frozen with $\Lambda = 3\Lambda_{\mathrm c}$.
		(b) Comparison of different magnetization components in the absence and presence (the inset) of an external magnetic field in the $z$-direction. 
		For both diagrams, ensemble averaging is performed on $50$ samples. 
		}
		\label{fig:5}
		\end{figure*}
		%%
		%
	%END_FOLD
	
	\subsection {b. Presence of External Magnetic Field}
	
	%BEGIN_FOLD  1st Paragraph
	
	The main objective of this study is to investigate the behavior of dipoles under external magnetic fields oriented in different Euclidean coordinate systems.  
	We found that the continuous phase transition disappears when the magnetic field is applied within the lattice plane along the $x$ or $y$-axis. 
	Although we did not include the corresponding diagram, Fig.~\ref{fig: 6-a} demonstrates this through the hysteresis diagram of magnetization along the $x$ direction \textit{versus} $B_{\mathrm{ext}}$ for a lattice with $1600$ dipoles. 
	The time gap of the dipoles aligning with the external field illustrates that they are ferromagnetic in the $x$ direction. 
	However, due to the symmetry in the $xy$ plane, similar results are expected when an external field is applied along the $y$ direction or a combination of both (not shown). 
	
	%END_FOLD
	
	%BEGIN_FOLD  2d Paragraph

	The comparison between the inset and the main figure in Fig.~\ref{fig: 6-b} demonstrates that applying an external magnetic field along the $z$-axis preserves the continuous phase transition, unlike when the field is aligned with the lattice plane. 
	This figure compares the different magnetization components when the nonzero magnetic field is applied only in $z$ direction ($\mathbf B_{\text{ext}}\cdot \hat{\mathbf k} \neq 0$) and with the zero external field ($\mathbf B_{\text{ext}} = 0$), highlighting that the ordering parameter does not change significantly with the vertical field.
	
	%END_FOLD
	
	%BEGIN_FOLD  3d Paragraph
	
	The main diagram in Fig.~\ref{fig: 6-b} illustrates that, in the absence of an external magnetic field, the average absolute values of $m_x$ and $m_y$ (denoted as $\langle |m_x| \rangle$ and $\langle |m_y| \rangle$) both contribute equally to the overall magnetization $\langle m \rangle$. 
	In contrast, the average absolute value of $m_z$ (denoted as $\langle |m_z| \rangle$) fluctuates around zero and is negligible. 
	Consequently, $\langle m_p \rangle$ and $\langle m \rangle$ overlap, indicating they are indistinguishable without the field.
	However, when $\mathbf B_{\text{ext}}\cdot \hat{\mathbf k} \neq 0$, $\langle m \rangle$ and $\langle m_p \rangle$ separate, as shown in the inset, indicating that $\langle m_z \rangle$ becomes a significant component of the total magnetization.   
	
	%END_FOLD
	
	%BEGIN_FOLD  4d Paragraph
	
	In the next step, we investigate whether the phase transition is preserved when the external magnetic field is applied vertically. 
	In other words, we determine the threshold field at which dipoles align with the exerted field and lose their spontaneous ordering for various lattice sizes.
	For a lattice with 1225 dipoles, we visualize this threshold through the parameters $m$, $m_p$, and $m_z$ for a single realization, plotted against the vertical field $B_z$ in Fig.~\ref{fig: 7}. 
	The figure shows that as $m_p$ decreases, $m_z$ increases. 
	Consequently, $m_z$ transforms from a linear relationship to a constant value, resulting in a collapse in the $m$ graph snd moving toward saturation limit.  
	This indicates the point at which the dipoles fully rotate out of the lattice plane and align with $B_z$, causing the spontaneous ordering to vanish completely. 
	
		%
		%%%% fig: 7, m components, B-z is on %%%%
		\begin{figure}[t]
		\centering
		\includegraphics[width=0.45\textwidth]{7.eps}
		\captionsetup{font=footnotesize, justification=raggedright}
		\caption{
		The variations in different magnetization components, including $m$, $m_z$, and $m_p$, are shown against the vertical magnetic field $B_z$ or a single sample. 
		The initial conditions are the same as those used in the hysteresis diagram in  Fig.~\ref{fig: 6-a}.
		}
		\label{fig: 7}
		\end{figure}
		%% 
		%
		
		%%% fig: 8, extrapor..., Bz) 	
		\begin{figure}[t]
		\centering
		\captionsetup{font=footnotesize, justification=raggedright}
		\includegraphics[width=0.5\textwidth]{8.eps}
		\caption{
		The relationship between the inverse threshold magnetic field, $b_\text c^{-1}$, and the reciprocal of the lattice length, $L^{-1}$, along the $z$-direction, following the linear function ${b_\mathrm c}^{-1} = 0.037 L^{-1} + 0.012$. 
		}
		\label{fig: 8}
		\end{figure}
		%%
		%
	
	%END_FOLD
	
	%BEGIN_FOLD  5th Paragraph
	
	Fig.\ref{fig: 8} determines the inverse of threshold vertical external field, denoted as $b_{\mathrm c}^{-1}$ for different lattice sizes. 
	For this purpose, we used the location of the dip in the $m$ curve, which is indicated by the solid circle in Fig.~\ref{fig: 7}. 
	The dip in $m$ curve of this figure provides a more precise estimate of $1/b_{\mathrm c}$ in comparison to other magnetization components.  
	The relationship is described by the formula $b_{\mathrm c}^{-1} = 0.037 L^{-1} + 0.012$, which linearly connects inverse of threshold external magnetic field and the size of the lattice. 
	The $y$-intercept of linear fit in Fig.~\ref{fig: 8} indicates that a magnetic field of approximately $83.33$ in our reduced unit system is required to align the dipoles in the thermodynamic limit.  
	
	%END_FOLD
	
	\section {Conclusion and Discussion} 
	
	%BEGIN_FOLD  1st p

	This study explored the critical behavior of a 2D triangular lattice of nanomagnetic dipoles.  
	These dipoles, fixed in position, exhibited rotational dynamics influenced by dipolar interactions and rotational Brownian motion within a low-Reynolds-number regime. 
	The system's behavior was analyzed in relation to the control parameter (reduced temperature), both in the absence and presence of static external magnetic fields.
	
	%END_FOLD
	
	%BEGIN_FOLD  2d p
	
	The collective behavior of the system was characterized using thermodynamic parameters such as magnetization, susceptibility, magnetic energy, and specific heat capacity. 
	Our results demonstrated a continuous phase transition in the absence of an external magnetic field, attributed to the long-range nature of dipolar interactions (Figs.~\ref{fig: 4-a} and \ref{fig: 4-b}). 
	This finding contrasts with models like the Heisenberg model, where the Mermin-Wagner theorem prohibits such transitions due to the dominance of short-range interactions. 
	
	%END_FOLD
	
	%BEGIN_FOLD  3d p
	
	Applying an external magnetic field in the lattice plane (xy-direction) eliminated the phase transition by aligning all dipoles with the field, even at low field strengths. 
	However, when the field was applied in the vertical z-direction, the phase transition persisted until the field strength exceeded a critical threshold. For various lattice sizes, we determined this threshold to be approximately $83.33$ in reduced units, extrapolated to the thermodynamic limit. 
	This indicates that dipoles prefer the xy-plane alignment unless a sufficiently strong vertical field forces realignment.
	
	%END_FOLD
	
	%BEGIN_FOLD  4th p
	
	- Biogenic magnetic nanoparticles (MNPs) have been identified in various organisms, including bees, ants, salmon, and homing pigeons \cite{Kirschvink1981, Kirschvink2001, Diebel2000, Eder2013, Shaw2015}.  
	However, MNPs were first discovered in magnetotactic bacteria in 1975 \cite{Blakemore1975, Schuler1999}. 
	In these bacteria, chains of magnetite and maghemite crystals are encased within membranes that function as a biogenic compass, allowing the bacteria to align with the Earth's geomagnetic field.  
	This capability enables the bacteria to navigate towards deeper layers of mud where they thrive, complementing their random walk-like movement \cite{Kalmijn1978, Kirschvink2001}.
	
	%END_FOLD
	
	%BEGIN_FOLD  5th p
	
	Inspired by magnetotactic bacteria, some theoretical models suggested that similar chains of MNPs are connected to the ion channels, and their interaction with the geomagnetic field creates a magnetic sensation. 
	Through the torques created by this interaction, chains rotate and cause the channels to open or close. 
	This process can result in neuronal firing, which creates a perception of the geomagnetic field called magnetoreception.   
	The gating process can depend on the field's direction, strength, or a combination of both, although these specifics are not crucial for our purpose. 
	Inspired by magnetotactic bacteria, theoretical models have proposed that similar chains of MNPs in other organisms might be linked to ion channels, with their interaction with the geomagnetic field generating a magnetic sensation. 
	The torques produced by this interaction could cause the chains to rotate, leading to the opening or closing of ion channels. 
	This process may trigger neuronal firing, resulting in the perception of the geomagnetic field, known as magnetoreception. 
	The gating process can depend on the field's direction, strength, or a combination of both, although these specifics are not crucial for our purpose. 
	Additionally, it is important to note that our study does not focus on the internal interactions with ion channels. 
	What matters is that a portion of the dipoles must be connected to ion channels, while the rest contribute to the overall interaction \cite{Khoddam2018}. 
	Although these neurons and their associated ion channel mechanisms have yet to be identified, neural data processing provides some clues. 
	For instance, in various species such as fish \cite{Cadiou2010, Walker1997}, birds \cite{Semm1990, Beason1996, Mora2004, Cadiou2010, Elbers2017}, and rodents \cite{Wegner2006} the ophthalmic branch of the trigeminal system (and equivalents) has been identified as the pathway through which magnetic sensory information is transmitted to the brain, as indicated by EEG data. -
	
	%END_FOLD
	
	%BEGIN_FOLD  6th p
	
	Now we aim to align our model with the biological system by incorporating relevant variables and assumptions. 
	We assume that the dipoles are fixed in position but can rotate freely in three dimensions within the lattice. 
	Similarly, we do not expect MNPs within an organism to move freely. 
	We set the distance between nearest dipoles at $l = 100\othermu\mathrm m$, based on previous studies \cite{Kirschvink1992, Khoddam2018}. 
	According to the literature, the volume number density of superclusters containing MNPs in the human dura and pia meninges is approximately $1000/\mathrm{mm^3}$, corresponding to an average center-to-center distance of $l = 100\othermu\mathrm m$. 
	In our model, each dipole represented a supercluster with the radius of $a \sim 85 \mathrm{nm}$. 
	like superclusters observed in human meninges, each dipole contains $100$ single-domain magnetic particles like $\mathrm{Fe_3O_4}$ with the total magnetic moment per dipole is estimated to be $1.4 \times 10^{-13} \mathrm {A.m^2}$ \cite{Kirschvink1992, Khoddam2018}. 
	
	%END_FOLD 
	
	%BEGIN_FOLD  7th p
	
	Secondly, our model assumes that dipoles exist within a viscous environment with the dynamic viscosity of water $\eta = 0.65 \text {mPa.s}$ at a temperature of $T = 310 \text{K}$ (body temperature). 
	This environment induces rotational Brownian motion in the dipoles, which we modeled using the Langevin equation in the low-Reynolds number regime. 
	This assumption is biologically reasonable since approximately. 
	However, from a dynamic perspective, the biological system aligns with our model if MNPs exhibit viscoelastic behavior, which simplifies the complexity introduced by protein chains in the cytoplasm \cite{Goychuk2015}. 
	
	%END_FOLD 
	
	%BEGIN_FOLD  8th p
	
	We also employed a 2D lattice in our simulations for feasibility. 
	In biological systems, MNPs are often arranged in layered structures within various organisms, such as in the dura mater and pia of the human body, the fat body tissues beneath the skin of honeybees' stomach, and specific regions in fish \cite{Shaw2015, ?}.
	Additionally, we selected a triangular lattice structure for our model because the computational work for this lattice was more feasible rather than other lattices. 
	However there is also biological reasons as well. 
	For example similar lattice shapes, though not rigidly organized, has been observed in the repeating patterns of neuronal clusters known as microcolumns in the visual and somatosensory cortices of mice, as well as in the language areas of the human brain \cite{Maruoka2017}. 
	
	%END_FOLD

	%BEGIN_FOLD  9th p
	
	While we examined our system's behavior in response to changes in the control parameter, we do not anticipate variations in dipole density or temperature. 
	We hypothesize that for a biological magnetic sensor to function effectively, it must operate near its critical point, maximizing susceptibility to weak geomagnetic fields. 
	This hypothesis is supported by an experiment in \cite{Khan2019}, where participants exposed to a $3\mathrm{T}$ magnetic field using an fMRI device exhibited long-lasting magnetic dipole patterns in their brains, as observed via MEG.
	This suggests the system is near its critical point—if it were below this point, the induced order would dissipate quickly after the field was removed; if above, the order would persist, resulting in permanent magnetization. 
	
	%END_FOLD
	
	%BEGIN_FOLD  10th p 
	
	As discussed, we determined the threshold for various lattices and found that a magnetic field strength of $2.5\mu\mathrm T$ in SI is required to align the dipoles in the thermodynamic limit.
	While this field strength may seem small, it is significant for two reasons. 
	First, the persistence of the phase transition contrasts with models like Heisenberg, where any nonzero external magnetic field in any direction eliminates the phase transition. 
	Second, it provides a potential numerical explanation for how ferromagnetic-based magnetoreceptors align with the geomagnetic field, contributing to magnetoreception in some animals. 
	Although this value is significantly lower than the average strength of the geomagnetic field ($25-65\ \othermu \text{T}$), it is reasonable given the assumptions and simplifications made in our model.
	There is no requirement that this limit also holds for other lattice types. 
	In fact, a continuous para-fero phase transition necessarily does not occur in other lattices. 
	For example, an order in the shape of an antiferromagnetic or microvortex appears in a square lattice. 
	
	%END_FOLD
	
	%BEGIN_FOLD  11th p
	 
	Future studies could extend this work by introducing flexible dipoles with both rotational and translational motion or developing quasi-3D models with layered dipole arrangements.
	Another possible direction is developing a quasi-three-dimensional model with dipoles arranged in two-dimensional layers, where interactions between layers at varying distances along the $z$-axis are considered, inspired by membrane structures. 
	
	%END_FOLD
	
	
	%\subsection{Ferromagnetic-Based Magnetoreception}  
	
	%BEGIN_FOLD 1st Paragraph 
	
	%Our study offers a pathway for analytically understanding the rotational dynamic behavior of biological systems composed of biogenic Magnetic Nanoparticles (MNPs) in response to geomagnetic fields, which is known as one aspect of the magnetic sense. 
	%Various experiments conducted on behavior and electrophysiology (EEG), along with detailed anatomical studies, have yielded evidence supporting that a wide range of organisms, from unicellular microorganisms to various mammals, can detect and utilize specific components of the geomagnetic field during both short and long journeys. 
	%These organisms exhibit a fundamental understanding of the magnetic direction and maps, enabling basic orientation and precise localization or navigation in more sophisticated instances \cite{Kirschvink2001, Kirschvink1981, Cadiou2010, Johnsen2005, Schuler2006, Johnsen2008, Shaw2015, Shao2020, Lohmann2013, Johnsen2005, Fransson2001, Mouritsen2017, Mouritsen2018}. 
	%Notable examples of organisms that demonstrate orienting behavior include pigeons, salmons, lobsters, bees, ants, and rats \cite{Kirschvink2001, Kirschvink1981, Cadiou2010, Johnsen2005, Schuler2006, Johnsen2008, Shaw2015}. On the other hand, migratory animals such as birds, rodents, fish, and reptiles utilize a combination of these parameters to determine their heading and/or location \cite{Shao2020, Lohmann2013, Johnsen2005, Fransson2001, Mouritsen2017, Mouritsen2018}. 
	
	%END_FOLD
	
	%BEGIN_FOLD %2d paragrpah
	
	%For such a remarkable sense, different types of related sensors have been suggested, such as magnetoreception or electroreception \cite{Kirschvink2001, Johnsen2005, Schuler2006, lohmann2010, Cadiou2010, Nordmann2017}, in which the first sensor can activate with either statistic or alternative magnetic field, but the second one only works with the alternative one.  
	%For such sensors and the subset interactions, three main models have been suggested: 1) electromagnetic induction, 2) the response of single-domain (SD) biogenic magnetic ferro/ferrimagnetic or superparamagnetic nanoparticles to magnetic fields, and 3) magnetic field-dependent chemical reactions (e.g., radical pair mechanism). 
	%Here, we focus on the ferromagnetic-based sensors and, hence, the second model.    
	%This study only focus on the second model and hence magnetosphere and only ferrommagnetic-based ones, such as magnetite/magemite.  
	
	%END_FOLD
	
	%BEGIN_FOLD %3d Paragraph
	
	%Magnetite ($\mathrm{Fe_3 O_4}$) is Earth's most prevalent magnetic mineral. 
	%It exhibits the highest level of magnetism among all natural iron oxides \cite{Cadiou2010}. 
	%More interestingly, nanometer-sized crystals of these have been discovered in various animals, including bees, ants, salmon, and homing pigeons, etc. \cite{Kirschvink1981, Kirschvink2001, Diebel2000, Eder2013, Shaw2015}. 
	%Initially, these crystals were observed within magnetotactic bacteria \cite{Blakemore1975, Schuler1999}. 
	%Further studies revealed that they possess a chain of magnetosome tissues composed of magnetite/magemite. 
	%Such a chain acts like a biological compass and helps the organ find direction towards deeper layers of the mud where they reside, in addition to their random walk-like movement \cite{Kalmijn1978, Kirschvink2001}.  
	
	%END_FOLD
	
	%BEGIN_FOLD %4th Paragraph
	
	%To name the animals' abality to sense geomagnetic fields a sense, relevant sensory neurons are required to convert the chemical or physical energy of the stimulus into an electrical signal that can be transmitted to the brain for processing. 
	%In various species such as fish \cite{Cadiou2010, Walker1997}, birds \cite{Semm1990, Beason1996, Mora2004, Cadiou2010, Elbers2017}, and rodents \cite{Wegner2006} the ophthalmic branch of the trigeminal system (and equivalents) has been identified as the pathway through which magnetic sensory information is transmitted to the brain, as indicated by EEG data. 
	%Although magnetoreception has been confirmed in many animals, only two genes are reported to be probably associated with magnetoreception in animals \cite{Ritz2000, Maeda2008, Rodgers2009, Mouritsen2010, Shao2020} %Shao2020 is main one. Notably, neurobiological evidencec continues occurred in a some birds such as bobolink bird, homing  pigeons \cite{Johnsen2005, Shaw2015, Cadiou2010}.  
	
	%END_FOLD
	
	%BEGIN_FOLD %5th Paragraph 
	
	%A theoretical model proposed that chains of ferromagnetic-based magnetoreceptors can be linked to specific ion channels \cite{Cadiou2010, Kirschvink1981, Kirschvink2001, Walker2008, Shaw2015}. 
	%Depending on the direction or strength of the geomagnetic field, these chains can rotate and create torque, causing the gates to unlock. 
	%Consequently, it can result in neural patterns that enable organisms to perceive and comprehend magnetic field characteristics \cite{Cadiou2010, Shaw2015}. 
	%However, it is essential to note that these models are primarily theoretical, and further research is needed to provide compelling evidence for their validity. 
	%Currently, the most extensively studied organisms with a magnetic sense are unicellular ones, such as magnetotactic bacteria.
	
	%END_FOLD
	
	%BEGIN_FOLD %6th paragraph
	
	%(Maybe it's better to not bring this paragraph!)
	%Crystals of MNPs, morphologically similar to magnetotactic bacteria, have also been detected in human brain tissue at concentrations of five million/g and $100$ million/g in the pia and dura, respectively, during an invasive experiment \cite{Kirschvink1992}.  
	%In a subsequent noninvasive study conducted in $2019$, EEG brain recordings revealed a distinct response to two ecologically relevant rotations of Earth-strength magnetic fields. 
	%The observed brain response depended on the downward, horizontal rotations of the static vertical magnetic field, indicating the sensitivity of human brains to the polarity of the field \cite{Kirschvink2019}. 
	%This finding rules out hypotheses involving cryptochrome-mediated quantum compass mechanisms or the reaction of superparamagnetic particles with magnetic fields.   
	%The EEG response exhibited a decrease in alpha-oscillation frequency within the range of $8-13 \mathrm {Hz}$ \cite{Kirschvink2019}, specifically in the form of alpha-ERD waves. 
	%These waves were consistently observed and are crucial as similar alpha-wave responses are typically seen during the processing of sensory and cognitive stimuli \cite{Peng2012}. 
	%This decrease in alpha-oscillation may indicate the activation of neurons involved in processing incoming sensory information, signifying a shift in neuronal activity from the internal resting rhythm to external engagement with sensory or task-related processing \cite{Pfurtscheller1999}.  
	
	%END_FOLD	
	
	% References
	%BEGIN_FOLD  
	
	\bibliography{References} % Replace "references" with the name of your .bib file
	\bibliographystyle{apsrev4-2} % Use the appropriate bibliography style.
	%END_FOLD

\end{document}


