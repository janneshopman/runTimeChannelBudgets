# Channel flow budgets during run-time

This method was developped to calculate the turbulent kinetic energy budgets of a channel flow during run-time, using OpenFOAM. It consists of two main parts:

* calcBudgets - A function object that, during run-time, calculates and time-averages the components necessary for the budget term calculations.
* channelBudgets - A post-processing utility that space-averages the components, which are then used to calculate and write the budget terms as a function of channel height.

## Authors

The post-processing utility was developped by Jannes Hopman of the Heat and Mass Transfer Technological Center, Technical University of Catalonia, C/Colom 11, 08222 Terrassa, Spain. 

## License

calcBudgets and channelBudgets are published under the GNU GPL Version 3 license, which can be found in the LICENSE file.

## Method

Reynolds averaged turbulent kinetic energy terms are a function of the fluctuating field variables: u\' = u - \<u\>, and similarly p\', where \<\> indicates time-averaging and space-averaging in the periodic directions.
One way to calculate these budgets is by writing instantaneous u fields during run-time, calculating the average field values in post-processing and substracting them to find the fluctuating variables. This method, however, can cost massive amounts of memory, write-time and result in lengthy post-processing.
This can be avoided by noting that the kinetic energy budget terms can be rewritten using, as an example:

* \<u\'u\'\> = \<uu\> - \<u\>\<u\>.

The terms on the right-hand side can be averaged during run-time and only have to be written at the final time-step of the simulation. The necessary terms are created, calculated and averaged by the calcBudgets functionObject.
The spatial averaging and the recombination of the terms on the right-hand side to form the budget term on the left-hand side is handled by the channelBudgets utility. This creates a directory with the calculated budget terms as a function of the channel-height.
Furthermore, a python script was included to nicely plot the terms and compare them to reference data of Vreman and Kuerten in: Vreman, A. W., & Kuerten, J. G. (2014). Comparison of direct numerical simulation databases of turbulent channel flow at Reτ= 180. Physics of Fluids, 26(1).

## Prerequisites

* OpenFOAM v2012. While it may compile against other versions, this is not tested and currently not supported.
* Python with numpy and matplotlib

## Usage

* Make sure that OpenFOAM v2012 is loaded into your environment 
* Compile "channelBudgets" with

<pre>
./Allwmake
</pre>

## calcBudgets

The calcBudgets function object can be found in "cases/templateCase/system/calcBudgets" and includes "initBudgets.H" in the same directory, to initiate the budget term components.
It is called from the controlDict, also in the same directory, by the lines:

<pre>
functions
{
    #include "calcBudgets"
}
</pre>

calcBudgets consists of two sub-functions: discreteBudgets and timeAverage. 

discreteBudgets:
* discreteBudgets contains the discretisations for the budget term components, which should be done in the exact same way as found in the solver.
* In the template case the discretisations are chosen for the symmetry-preserving method, but should be changed accordingly by the user.

timeAverage:
* timeAverage averages all the components. In the template case, averaging starts after 15 time units and the fields are written only at the end of simulation.
* Intermidiate writing can be done by changing the "writeControl" variable from "onEnd" to, for example, "writeTime".
* Resetting the average and manually ensemble averaging the output can be done by changing "restartOnOutput" from "false" to "true".

## channelBudgets

channelBudgets can be found in the "applications/utilities/channelBudgets" directory. After compilation, it is run when the simulation has ended, by using:

<pre>
channelBudgets -latestTime
</pre>

* the "-latestTime" option should be left away if intermediate field averages are output by calcBudgets.
* The utility is based on the "postChannel" utility. It reads the budget component fields in "readFields.H", combines them to form the budget terms in "calculateFields.H" and finally applies spatial averaging in "collapse", after which the resulting line plots are written to "graphs/\<timeDirectory\>".
* The utility reads the "postChannelDict" inside the "constant" directory, containing mesh information for averaging. An example is found in "cases/templateCase/constant/postChannelDict".

## Test case

The test case can be found in the "cases/templateCase" directory.
This directory should be copied before it is run from inside the new directory with:

<pre>
./run.sh
</pre> 

* This runs the case in parallel and automatically runs the post-processing afterwards, to create the data files in the "graphs" directory.
* The templateCase was set up to be run with RKSymFoam using Runge-Kutta 3 temporal integration.
* Any desired solver, for example "icoFoam" can be used by changing the "application" variable in the "system/controlDict": 

<pre>
application     RKSymFoam;
</pre>

## Post-processing

To post-process the cases, run "plotBudgets.py" from the "cases/\<case\>/postProcess" directory using

<pre>
python plotBudgets.py
</pre>

* The endTime and nu variables have to be set, see the template case for examples.
* Budget terms are graphed with data of Vremand and Kuerten as a reference.
* Resulting plots will be found in the "postProcess/results" directory.

## Contact & support

For bug reports or support, feel free to contact Jannes Hopman at jannes.hopman@upc.edu. Please note that this code is not maintained nor regularly updated, and is only tested with OpenFOAM v2012.
Questions related to other versions will thus not be answered. 

## Disclaimer

calcBudgets and channelBudgets are  provided by the copyright holders and contributors "as-is" and any express or implied warranties, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose are disclaimed. 
In no event shall the copyright owner or contributors be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, procurement of substitute goods or services; loss of use, data, or profits; or business interruption) however caused and on any theory of liability, whether in contract, strict liability, or tort (including negligence or otherwise) arising in any way out of the use of this software, even if advised of the possibility of such damage.
