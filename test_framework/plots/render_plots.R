library(tidyverse)
library(ggpubr)
library(svglite)

setwd("~/bioinformatics/hmm/git_hmmmlib/test_framework/plots")
#data <- read_csv("../time2.csv",)
#data <- read_csv("../short.csv")
#data <- read_csv("../medium.csv")
#data <- read_csv("../oct-31.csv")
data <- read_csv("../oct-31-2.csv")



data_grouped = data %>% group_by(observations, algorithm, variant) %>% 
    summarise(mean = mean(time), sd = sd(time)) 




p_mean = data_grouped %>% ggplot(aes(observations, mean, color = variant)) +
    geom_point() + 
    geom_line() + 
    geom_errorbar(aes(ymin=(mean-sd), ymax=(mean+sd) ), width = 10000) +
    facet_wrap(.~algorithm, scales = "free") +
    labs(y = "mean time [s]", caption = "error bars: standard deviation")
p_mean

p_mean_normalized = data_grouped %>% ggplot(aes(observations, mean/observations, color = variant)) +
    geom_point() + 
    geom_line() + 
    geom_errorbar(aes(ymin=(mean-sd)/observations, ymax=(mean+sd)/observations ), width = 10000) +
    facet_wrap(.~algorithm, scales = "free") +
    labs(y = "normalized mean time [s]", caption = "error bars: standard deviation")
p_mean_normalized


ggsave("all.pdf", height = 5, width = 7, plot = p_mean)
ggsave("all_normalized.pdf", height = 5, width = 7, plot = p_mean_normalized)



















# old non-generalized
plot_1 = data_processed %>% ggplot(aes(observations, mean)) +
    geom_point() + 
    geom_errorbar(aes(ymin=mean-sd, ymax=mean+sd)) +
    labs(y = 'mean time')


plot2 = data_processed %>% ggplot(aes(observations, mean/observations)) +
    geom_line() + 
    geom_errorbar(aes(ymin=mean/observations-sd, ymax=mean/observations+sd)) +
    labs(y = 'mean time normalized')



ggarrange(plot_1, plot2, ncol = 1, nrow = 2, align = "v")

ggsave("viterbi.png", height = 5, width = 8)
