//Parameters list for beta prime precipitation evolution problem

//define problem dimensions
#define problemDIM 3
#define spanX 7.2 //14.0
#define spanY 18.0 //14.0
#define spanZ 18.0 //10.0 //14.0

//define mesh parameters
#define subdivisionsX 2
#define subdivisionsY 5
#define subdivisionsZ 8
#define refineFactor 4
#define finiteElementDegree 2

//define time step parameters
#define timeStep (2.4e-4) //(1.3e-7) //5e-6 //1.67e-5
#define timeIncrements 10000 //1000000 //200000
#define timeFinal 100000000 //(timeStep*timeIncrements)
#define skipImplicitSolves 1

//define solver parameters
#define solverType SolverCG
#define abs_tol true
#define relSolverTolerance 1.0e-2
#define absSolverTolerance 1.0e-3
#define maxSolverIterations 10000

//define results output parameters
#define writeOutput true
#define skipOutputSteps (timeIncrements/10) //50000 //timeIncrements/10 //5000

// flag to allow or disallow nucleation
#define nucleation_occurs false

#define num_sop 1							// for now, must be between 1 and 3
#define numFields (1+num_sop+problemDIM)

//define Cahn-Hilliard parameters (No Gradient energy)
#define M0cV 1.0

//define Allen-Cahn parameters
#define Mn1V 40.0
#define Mn2V 50.0
#define Mn3V 50.0

// define gradient penalty tensors
//double Kn1[3][3]={{0.0280,0,0},{0,0.0350,0},{0,0,0.0107}}; // Gen 1 B'''
//double Kn1[3][3]={{0.0265,0,0},{0,0.0331,0},{0,0,0.0101}}; // Gen 2 B'''
double Kn1[3][3]={{0.04036,0,0},{0,0.05042,0},{0,0,0.01535}}; // Gen 3 B'''
double Kn2[3][3]={{0.123,0,0},{0,0.123,0},{0,0,0.123}};
double Kn3[3][3]={{0.123,0,0},{0,0.123,0},{0,0,0.123}};

//define energy barrier coefficient (used to tune the interfacial energy)
#define W -0.1

// Define Mechanical properties
#define n_dependent_stiffness true
// Mechanical symmetry of the material and stiffness parameters
#if problemDIM==1
	// Used throughout system if n_dependent_stiffness == false, used in n=0 phase if n_dependent_stiffness == true
	#define MaterialModelV ISOTROPIC
	#define MaterialConstantsV {22.5,0.3}
	// Used in n=1 phase if n_dependent_stiffness == true
	#define MaterialModelBetaV ISOTROPIC
	#define MaterialConstantsBetaV {22.5,0.3}

#elif problemDIM==2
	// Used throughout system if n_dependent_stiffness == false, used in n=0 phase if n_dependent_stiffness == true
	// 2D order of constants ANISOTROPIC - 6 constants [C11 C22 C33 C12 C13 C23]
	#define MaterialModelV ANISOTROPIC
	#define MaterialConstantsV {31.3,31.3,6.65,13.0,0.0,0.0} //scaled by E* = 2e9 J/m^3
	// Used in n=1 phase if n_dependent_stiffness == true
	#define MaterialModelBetaV ANISOTROPIC
	#define MaterialConstantsBetaV {23.35,30.25,36.35,15.35,0.0,0.0} //scaled by E* = 2e9 J/m^3

#elif problemDIM==3
	// Used throughout system if n_dependent_stiffness == false, used in n=0 phase if n_dependent_stiffness == true
	#define MaterialModelV ANISOTROPIC
	// 3D order of constants ANISOTROPIC - 21 constants [11, 22, 33, 44, 55, 66, 12, 13, 14, 15, 16, 23, 24, 25, 26, 34, 35, 36, 45, 46, 56]
	//#define MaterialConstantsV {62.6,62.6,64.9,13.3,13.3,18.3,26.0,20.9,0,0,0,20.9,0,0,0,0,0,0,0,0,0} //these are in GPa-need to be non-dimensionalized
	#define MaterialConstantsV {31.3,31.3,32.45,6.65,6.65,9.15,13.0,10.45,0,0,0,10.45,0,0,0,0,0,0,0,0,0} //scaled by E* = 2e9 J/m^3
	// Used in n=1 phase if n_dependent_stiffness == true
	#define MaterialModelBetaV ANISOTROPIC
	#define MaterialConstantsBetaV {23.35,30.25,36.35,8.2,16.7,14.45,15.35,14.35,0,0,0,7.25,0,0,0,0,0,0,0,0,0} //scaled by E* = 2e9 J/m^3

#endif


// Stress-free transformation strains
// Linear fits for the stress-free transformation strains in for sfts = sfts_linear * c + sfts_const

// B'''
double sfts_linear1[3][3] = {{-0.34358,0,0},{0,0.68568,0},{0,0,0.19308}};
double sfts_const1[3][3] = {{0.14978,0,0},{0,-0.10254,0},{0,0,-0.034049}};

//B''' at the equivalent of x_Nd = 0.20
//double sfts_linear1[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
//double sfts_const1[3][3] = {{0.081064,0,0},{0,0.034596,0},{0,0,0.004567}};

//B''' at the equivalent of x_Nd = 0.175
//double sfts_linear1[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
//double sfts_const1[3][3] = {{0.0896535,0,0},{0,0.017454,0},{0,0,-2.6e-4}};

//B''' at the equivalent of x_Nd = 0.15
//double sfts_linear1[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
//double sfts_const1[3][3] = {{0.098243,0,0},{0,3.12e-4,0},{0,0,-0.005087}};

//B''' at the equivalent of x_Nd = 0.125
//double sfts_linear1[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
//double sfts_const1[3][3] = {{0.1068,0,0},{0,-0.01683,0},{0,0,-0.009914}};

// 2D test values
//double sfts_linear1[3][3] = {{0.1568,0,0},{0,0.1568,0},{0,0,0.1568}};
//double sfts_const1[3][3] = {{-0.02756,0,0},{0,-0.02756,0},{0,0,-0.02756}};

double sfts_linear2[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
double sfts_const2[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

double sfts_linear3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
double sfts_const3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

//define free energy expressions (Mg-Nd data from CASM) (B''', gen 2)
#define faV (64.996*c*c - 1.681*c + 0.00010277)
#define facV (129.992*c - 1.681)
#define faccV (129.992)
#define fbV (2.1479*c*c - 2.1743*c + 0.033684)
#define fbcV (4.2958*c - 2.1743)
#define fbccV (4.2958)

////define free energy expressions (Mg-Nd data from CASM) (B''', gen 1)
//#define faV (46.599*c*c - 1.6907*c + 0.00010827)
//#define facV (93.198*c - 1.6907)
//#define faccV (93.198)
//#define fbV (2.1479*c*c - 2.1743*c + 0.033684)
//#define fbcV (4.2958*c - 2.1743)
//#define fbccV (4.2958)

//define free energy expressions (Mg-Nd data from CASM) (B', gen 1)
//#define faV (44.547*c*c - 1.6954*c + 0.00011001)
//#define facV (89.094*c - 1.6954)
//#define faccV (89.094)
//#define fbV (12.818*c*c - 4.8583*c + 0.19988)
//#define fbcV (25.636*c - 4.8583)
//#define fbccV (25.636)

#define h1V (3.0*n1*n1-2.0*n1*n1*n1)
#define h2V (3.0*n2*n2-2.0*n2*n2*n2)
#define h3V (3.0*n3*n3-2.0*n3*n3*n3)
#define hn1V (6.0*n1-6.0*n1*n1)
#define hn2V (6.0*n2-6.0*n2*n2)
#define hn3V (6.0*n3-6.0*n3*n3)

#define h1strainV (h1V*h1V*h1V*h1V*h1V)
#define h2strainV (h2V*h2V*h2V*h2V*h2V)
#define h3strainV (h3V*h3V*h3V*h3V*h3V)
#define hn1strainV (5.0*h1V*h1V*h1V*h1V*hn1V)
#define hn2strainV (5.0*h2V*h2V*h2V*h2V*hn2V)
#define hn3strainV (5.0*h3V*h3V*h3V*h3V*hn3V)

// This double-well function can be used to tune the interfacial energy
#define fbarrierV (n1*n1-2.0*n1*n1*n1+n1*n1*n1*n1)
#define fbarriernV (2.0*n1-6.0*n1*n1+4.0*n1*n1*n1)

// Calculate the Cahn-Hilliard mobility, which depends on the order parameter
#define McV (M0cV/((1.0-h1V)*faccV+(h1V)*fbccV))

// Residuals
#define rcV   (c)
#define rcxTemp ( cx*((1.0-h1V)*faccV+(h1V)*fbccV) + n1x*(fbcV-facV)*hn1V + grad_mu_el)
#define rcxV  (constV(-timeStep)*McV*rcxTemp)

#define rn1V   (n1-constV(timeStep*Mn1V)*((fbV-faV)*hn1V+W*fbarriernV+nDependentMisfitAC1+heterMechAC1))
#define rn2V   (n2-constV(timeStep*Mn2V)*((fbV-faV)*hn2V))
#define rn3V   (n3-constV(timeStep*Mn3V)*((fbV-faV)*hn3V))
#define rn1xV  (constV(-timeStep*Mn1V)*Knx1)
#define rn2xV  (constV(-timeStep*Mn2V)*Knx2)
#define rn3xV  (constV(-timeStep*Mn3V)*Knx3)

// Initial geometry
#define x_denom 3.0976
#define y_denom 68.0625
#define z_denom 44.2225
#define initial_interface_coeff 0.01
#define initial_radius 1.0
#define c_matrix 1.0e-2
#define c_precip 0.16
#define adjust_avg_c false
#define c_avg 0.004

#define calc_energy true

