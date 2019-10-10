library(tidyverse)

viterbi_normal <- read_csv("viterbi_normal.csv",)

viterbi_normal_processed = viterbi_normal %>% group_by(observations) %>% 
    summarise(mean = mean(time), sd = sd(time)) 

viterbi_normal_processed %>% ggplot(aes(observations, mean)) +
    geom_line() + 
    geom_errorbar(aes(ymin=mean-sd, ymax=mean+sd)) +
    labs(y = 'mean time')


