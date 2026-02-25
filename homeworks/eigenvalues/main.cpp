#include"matrix.hpp" 
#include<vector> 
#include<iostream> 
#include<random>
#include<cmath>


pp::matrix random_symmetric_matrix(int n) {
    // Random device for seeding
    std::random_device rd;

    // Mersenne Twister engine
    std::mt19937 gen(rd());

    // Uniform distribution between 0 and 1
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    pp::matrix A(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A.cols[j][i] = dist(gen);
        }
    }
    // make it symmetric: A = (A + A^T) / 2
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            A[i][j] = A[j][i] = 0.5 * (A[i][j] + A[j][i]);
        }
    }
    return A;
}

pp::vector random_vector(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> dist(0.0, 1.0);
    pp::vector b(n);

    for (int j=0; j<n; j++) {
        b[j] = dist(gen);
    }
    return b;
}

struct jacobi{
    int timesJ(pp::matrix& A, int p, int q, double theta) {  //pass A as reference else while loop gets stuck
       	double c=cos(theta),s=sin(theta);
	    for(int i=0;i<A.size1();i++){
            double aip=A[i][p],aiq=A[i][q];
            A[i][p]=c*aip-s*aiq;
            A[i][q]=s*aip+c*aiq;
		    }
        return 0;
    }
    int Jtimes(pp::matrix& A, int p, int q, double theta) {  // pass A as reference else while loop gets stuck
       	double c=cos(theta),s=sin(theta);
        for(int j=0;j<A.size1();j++){
            double apj=A[p][j],aqj=A[q][j];
            A[p][j]= c*apj+s*aqj;
            A[q][j]=-s*apj+c*aqj;
            }
        return 0;
    }

    std::pair<pp::vector, pp::matrix> cyclic(pp::matrix M) {
        pp::matrix A=M.copy();
        pp::matrix V=M.copy();
        V.setid();
        pp::vector w(M.size1());
        /* run Jacobi rotations on A and update V */
        /* copy diagonal elements into w */
        bool changed;
        do{
            changed=false;
            int n = M.size1();
            for(int p=0;p<n-1;p++)
            for(int q=p+1;q<n;q++){
                double apq=A[p][q], app=A[p][p], aqq=A[q][q];
                double theta=0.5*std::atan2(2*apq,aqq-app);
                double c=std::cos(theta),s=std::sin(theta);
                double new_app=c*c*app-2*s*c*apq+s*s*aqq;
                double new_aqq=s*s*app+2*s*c*apq+c*c*aqq;
                if(new_app!=app || new_aqq!=aqq) {// do rotation
                    changed=true;
                    timesJ(A,p,q, theta); // A←A*J 
                    Jtimes(A,p,q, -theta); // A←JT*A 
                    timesJ(V,p,q, theta); // V←V*J
                    }
            }
        }while(changed);

        for (int i = 0; i < A.size1(); i++) {
            w[i] = A[i][i];
        }
        return {w, V};
        }
};

int main(int argc, char** argv) {
    // PART 1
    std::cout << "----------PART A----------" << std::endl;
    int n = std::stoi(argv[1]);
    pp::matrix A = random_symmetric_matrix(n);

    std::cout << "-----Checking jacobi-----" << std::endl;
    A.print("A=");
    jacobi j;
    auto [w, V] = j.cyclic(A);
    V.print("V = ");
    w.print("w = ");
    pp::matrix D = V.transpose() * A * V;
    D.print("D =");
    pp::matrix VDV = V * D * V.transpose();
    VDV.print("V * D * V^T = A =");

    pp::matrix VVT = V * V.transpose();
    pp::matrix VTV = V.transpose() * V;
    VVT.print("V * V^T = ");
    VTV.print("V^T * V = ");

    // PART 2
    std::cout << "----------PART B----------" << std::endl;

    // PART 3'
    std::cout << "----------PART C----------" << std::endl;

    return 0;
}