library(tidyverse)
library(ggpubr)

viterbi_normal <- read_csv("bioinformatics/hmm/hmmmlib/test_framework/plots/viterbi_normal.csv",)

viterbi_normal_processed = viterbi_normal %>% group_by(observations) %>% 
    summarise(mean = mean(time), sd = sd(time)) 

viterbi_plot_1 = viterbi_normal_processed %>% ggplot(aes(observations, mean)) +
    geom_point() + 
    geom_errorbar(aes(ymin=mean-sd, ymax=mean+sd)) +
    labs(y = 'mean time')


viterbi_plot_2 = viterbi_normal_processed %>% ggplot(aes(observations, mean/observations)) +
    geom_line() + 
    geom_errorbar(aes(ymin=mean/observations-sd, ymax=mean/observations+sd)) +
    labs(y = 'mean time normalized')



ggarrange(viterbi_plot_1, viterbi_plot_2, ncol = 1, nrow = 2, align = "v")

ggsave("viterbi.png", height = 4, width = 8)
