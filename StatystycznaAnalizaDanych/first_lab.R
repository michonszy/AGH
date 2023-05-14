#wektor z ocenami
c(1,3,5,5,4,4,4,2,3,4)
oceny.transmutacja <- c(1,3,5,5,4,4,4,2,3,4)

summary(oceny.transmutacja)
#pakiet podstawowy

#podstawowe statystyki
summary <- summary(oceny.transmutacja)
quantile(oceny.transmutacja)
range(oceny.transmutacja)

library(moments)
As <- skewness(oceny.transmutacja)
K <- kurtosis(oceny.transmutacja)

Mo <- modeest::mfv(oceny.transmutacja)
statystyki.opisowe <- cbind(summary,As,K)
