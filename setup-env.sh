if [ "X$(basename -- "$0")" "==" "Xsetup-env.sh" ]; then
    echo "Source this file (do NOT execute it!) to set up the nRF52840 M.2 Developer Kit environment."
    exit
fi

# identify nrf52840-m2-devkit source tree root directory
export NRF52840_M2_ROOT=$( builtin cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
echo NRF52840_M2_ROOT: $NRF52840_M2_ROOT