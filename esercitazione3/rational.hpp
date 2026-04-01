#pragma once
#include <concepts>
#include <ostream>
#include <numeric>

template <typename I> requires std::integral<I>
class Rational {
    // di defualt sono privati nelle classi -> non accessibili dall'esterno
    I num_;  // numeratore
    I den_;  // denominatore

    void set_nan(){
        this->num_ = 0;
        this->den_ = 0;
    }

    void set_inf(bool is_negative){
        this->num_ = is_negative ? -1 : 1;
        this->den_ = 0;
    }

    public:
        // Costruttore di default
        Rational() : num_(0), den_(1) {}

        // Costruttore con parametri
        Rational(I num, I den) : num_(num), den_(den) {}

        // Metodi per la gestione dei casi speciali
        // 0/0 -> NaN
        bool is_nan() const {
            return this->num_ == 0 && this->den_ == 0;
        }

        // x/0 -> Inf
        bool is_inf() const {
            return this->den_ == 0 && this->num_ != 0;
        }

        // 0/x -> 0
        bool is_zero() const {
            return this->num_ == 0 && this->den_ != 0;
        }

        // Metodi getter
        I num() const {
            return this->num_;
        }

        I den() const {
            return this->den_;
        }

        // Metodi per operational overloading
        // Per stampare un Rational
        friend std::ostream& operator<<(std::ostream& os, const Rational<I>& r){
            if (r.is_nan()) os << "NaN";  // caso 0/0 indeterminato 
            else if (r.is_inf()) {
                std::string segno = r.num() > 0 ? "" : "-";
                os << segno << "Inf";
            }  // caso x/0 con x != 0
            else if (r.is_zero()) os << "0";  // caso 0/x con x != 0
            else {
                I gcd = std::gcd(r.num(), r.den()); // semplifichiamo la frazione prima di stamparla
                std::string segno = (r.num() * r.den() < 0) ? "-" : "";
                os << segno << std::abs(r.num()) / gcd << "/" << std::abs(r.den()) / gcd;
            }
            return os;
        }
        
        // Metodo per incrementare un Rational
        Rational<I> operator+=(const Rational<I>& other) {
            bool any_nan = this->is_nan() || other.is_nan();  // c'è almeno un nan?
            bool opp_inf = this->is_inf() && other.is_inf() && this->num() * other.num() < 0;  // i due sono inf di segno opposto?
            bool any_inf = this->is_inf() || other.is_inf();  // c'è almeno un inf?
            
            if (any_nan || opp_inf) {  // Se uno dei due è NaN o i due sono Inf di segno opposto, il risultato è NaN
                this->set_nan();
                return *this;
            }

            if (any_inf) {  // Se c'è almeno un inf, il risultato è Inf con il segno dato da chi ha "più peso" (ovvero chi è Inf)
                bool segno = this->is_inf() ? this->num() < 0 : other.num() < 0;  // ti chiedi se il primo è Inf, in tal caso prendi il segno del primo, altrimenti prendi il segno del secondo
                this->set_inf(segno);
                return *this;
            }
            
            // se arriviamo qui è perchè nessuno dei due è NaN o Inf
            this->num_ = this->num_ * other.den() + other.num() * this->den();
            this->den_ = this->den_ * other.den();
            return *this;
        }

        // Metodo per la somma tra due Rational
        Rational<I> operator+(const Rational<I>& other) const {
            Rational<I> result = *this;
            result += other;
            return result;
        }

        // Metodo per il decremento di un Rational
        Rational<I> operator-=(const Rational<I>& other) {
            *this += Rational<I>(-other.num(), other.den());  // Uso l'operatore += per fare la sottrazione usando l'opposto di other
            return *this;
        }

        // Metodo per la sottrazione tra due Rational
        Rational<I> operator-(const Rational<I>& other) const {
            Rational<I> result = *this;
            result -= other;
            return result;
        }

        // Metodo per la moltiplicazione 
        Rational<I> operator*=(const Rational<I>& other) {
            bool any_nan = this->is_nan() || other.is_nan(); // c'è almeno un nan?
            bool zero_times_inf = (this->is_zero() && other.is_inf()) || (this->is_inf() && other.is_zero()); // uno è zero e l'altro è inf?
            bool un_inf = this->is_inf() || other.is_inf(); // c'è almeno un inf?

            if (any_nan || zero_times_inf) {  // Se uno dei due è NaN o uno è zero e l'altro è Inf, il risultato è NaN
                this->set_nan();
                return *this;
            }

            if (un_inf) {  // Se c'è almeno un inf, il risultato è Inf con il segno dato dal segno complessivo dei due razionali
                bool this_neg = (this->num() < 0) != (this->den() < 0);
                bool other_neg = (other.num() < 0) != (other.den() < 0);
                this->set_inf(this_neg != other_neg);
                return *this;
            }

            this->num_ *= other.num();
            this->den_ *= other.den();
            return *this;
        }

        // Metodo per la moltiplicazione tra due Rational
        Rational<I> operator*(const Rational<I>& other) const {
            Rational<I> result = *this;
            result *= other;
            return result;
        }

        // Metodo per la divisione
        Rational<I> operator/=(const Rational<I>& other) {
            *this *= Rational<I>(other.den(), other.num());  // Uso l'operatore *= per fare la divisione usando il reciproco di other
            return *this;
        }

        // Metodo per la divisione tra due Rational
        Rational<I> operator/(const Rational<I>& other) const {
            Rational<I> result = *this;
            result /= other;
            return result;
        }

};