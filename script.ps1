# List of years to process
$years = 1918, 1919, 1949, 1958, 1969, 1979, 1984, 1995, 2002, 2009, 2016

# Base path to counties
$county_path = Resolve-Path .\validation\counties
$counties = Get-ChildItem -Path $county_path -Directory

$totalCounties = $counties.Count
$currentCountyIndex = 0

foreach ($county in $counties) {
    $currentCountyIndex++

    $households_path = "$county_path\$county\households"
    $households = Get-ChildItem -Path $households_path -Directory

    $totalHouseholds = $households.Count
    $currentHouseholdIndex = 0

    foreach ($household in $households) {
        $currentHouseholdIndex++

        $totalYears = $years.Length
        $currentYearIndex = 0

        foreach ($year in $years) {
            $currentYearIndex++

            # Display progress bar for Counties
            $countyProgress = ($currentCountyIndex / $totalCounties) * 100
            # Display progress bar for Households nested inside County progress
            $householdProgress = ($currentHouseholdIndex / $totalHouseholds) * 100
            # Display progress bar for Years nested inside Household progress
            $yearProgress = ($currentYearIndex / $totalYears) * 100

            Write-Progress -PercentComplete $countyProgress -Status "Processing Counties" -Activity "$county ($currentCountyIndex of $totalCounties)"
            Write-Progress -Id 1 -PercentComplete $householdProgress -Status "Processing Households of $county" -Activity "$household ($currentHouseholdIndex of $totalHouseholds)"
            Write-Progress -Id 2 -PercentComplete $yearProgress -Status "Processing Years for $household" -Activity "$year ($currentYearIndex of $totalYears)"

            $exitCode = python .\run_v.py $county $household $year

            # Check the exit code
            if ($exitCode -eq 1) {
                # Break out of the years loop and move to the next household
                break
            }
        }

        Write-Progress -Id 2 -Clear
    }

    Write-Progress -Id 1 -Clear
}

Write-Progress -Clear
