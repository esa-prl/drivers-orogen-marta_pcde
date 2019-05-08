require 'orocos'
require 'readline'
include Orocos


## Initialize orocos ##
Orocos.initialize

## Execute the task 'messages::Producer' ##
Orocos.run 'pcde::Task' => 'pcde' do
    ## Get the task context##
    driver = Orocos.name_service.get 'pcde'

    ## Configure the task
    driver.configure

    ## Start the task ##
    driver.start

    Readline::readline("Press Enter to exit\n") do
       end
    
    # battery = driver.battery_voltage.reader
    # mcs_reader = driver.MCS_status.reader
    # external_reader = driver.external_voltage.reader
end